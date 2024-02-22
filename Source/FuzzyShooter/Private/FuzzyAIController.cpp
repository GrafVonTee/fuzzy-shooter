// Fill out your copyright notice in the Description page of Project Settings.


#include "FuzzyAIController.h"
#include "UObject/NameTypes.h"

#include "FuzzyLib/Term/Gaussian.h"
#include "FuzzyLib/Term/Trapezoid.h"

#include "FuzzyLib/Variable/MaxReceiver.h"
#include "FuzzyLib/Accumulation/MaxAccumulation.h"
#include "FuzzyLib/Activation/ProdActivation.h"
#include "FuzzyLib/Aggregation/MinAggregation.h"
#include "FuzzyLib/Defuzzification/CentroidDefuzzification.h"

#include "FuzzyLib/Hedge/HedgeNot.h"
#include "FuzzyLib/Hedge/HedgeVery.h"
#include "FuzzyLib/Hedge/HedgeApproximately.h"

#include "UObject/Object.h"

#include "AgentCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/EngineTypes.h"


AFuzzyAIController::AFuzzyAIController()
{
}

void AFuzzyAIController::BeginPlay()
{
	Super::BeginPlay();

	Health = NewObject<UVariable>();
	Ammo = NewObject<UVariable>();
	Action = NewObject<UVariable>();
	MovingAction = NewObject<UVariable>();

	Aggregation = NewObject<UMinAggregation>();
	Activation = NewObject<UProdActivation>();
	Accumulation = NewObject<UMaxAccumulation>();
	Receiver = NewObject<UMaxReceiver>();
	Defuzzification = NewObject<UCentroidDefuzzification>();

	ActionRuleBlock = NewObject<URuleBlock>();
	MovingRuleBlock = NewObject<URuleBlock>();

	HedgeNot = NewObject<UHedgeNot>();
	HedgeVery = NewObject<UHedgeVery>();
	HedgeApprox = NewObject<UHedgeApproximately>();

	SetHealthVariable();
	SetAmmoVariable();
	SetActionVariable();
	SetMovingActionVariable();

	SetActionRuleBlock();
	SetMovingRuleBlock();

	BeginReacting();
	ResetReactionTimer();

}

void AFuzzyAIController::SetHealthVariable()
{
	Health->Set("Health", 0, 150, Receiver);

	UTrapezoid* HealthLow = NewObject<UTrapezoid>();
	HealthLow->Set(
		"Low",
		Health->LowerBound,
		Health->UpperBound,
		0,
		0,
		40,
		70
	);
	Health->AddTerm(HealthLow->Name, HealthLow);

	UTrapezoid* HealthEnough = NewObject<UTrapezoid>();
	HealthEnough->Set(
		"Enough",
		Health->LowerBound,
		Health->UpperBound,
		40,
		70,
		90,
		110
	);
	Health->AddTerm(HealthEnough->Name, HealthEnough);

	UTrapezoid* HealthMany = NewObject<UTrapezoid>();
	HealthMany->Set(
		"Many",
		Health->LowerBound,
		Health->UpperBound,
		90,
		110,
		150,
		150
	);
	Health->AddTerm(HealthMany->Name, HealthMany);
}

void AFuzzyAIController::SetAmmoVariable()
{
	Ammo->Set("Ammo", 0, 150, Receiver);
	UTrapezoid* AmmoLow = NewObject<UTrapezoid>();
	AmmoLow->Set(
		"Low",
		Ammo->LowerBound,
		Ammo->UpperBound,
		0,
		0,
		40,
		60
	);
	Ammo->AddTerm(AmmoLow->Name, AmmoLow);

	UTrapezoid* AmmoEnough = NewObject<UTrapezoid>();
	AmmoEnough->Set(
		"Enough",
		Ammo->LowerBound,
		Ammo->UpperBound,
		40,
		60,
		90,
		110
	);
	Ammo->AddTerm(AmmoEnough->Name, AmmoEnough);

	UTrapezoid* AmmoMany = NewObject<UTrapezoid>();

	AmmoMany->Name = "Many";
	AmmoMany->Set(
		"Many",
		Ammo->LowerBound,
		Ammo->UpperBound,
		90,
		110,
		150,
		150
	);
	Ammo->AddTerm(AmmoMany->Name, AmmoMany);

}

void AFuzzyAIController::SetActionVariable()
{
	Action->Set("Action", 0, 100, Receiver);

	UGaussian* Run = NewObject<UGaussian>();
	Run->Set(
		"Run",
		Action->LowerBound,
		Action->UpperBound,
		0,
		50
	);
	Action->AddTerm(Run->Name, Run);

	UGaussian* Shoot = NewObject<UGaussian>();
	Shoot->Set(
		"Shoot",
		Action->LowerBound,
		Action->UpperBound,
		100,
		50
	);
	Action->AddTerm(Shoot->Name, Shoot);

}

void AFuzzyAIController::SetMovingActionVariable()
{
	MovingAction->Set("Moving Action", 0, 150, Receiver);

	UGaussian* Hide = NewObject<UGaussian>();
	Hide->Set(
		"Hide",
		MovingAction->LowerBound,
		MovingAction->UpperBound,
		0,
		50
	);
	MovingAction->AddTerm(Hide->Name, Hide);

	UGaussian* GoToMedKit = NewObject<UGaussian>();
	GoToMedKit->Set(
		"MedKit",
		MovingAction->LowerBound,
		MovingAction->UpperBound,
		50,
		50
	);
	MovingAction->AddTerm(GoToMedKit->Name, GoToMedKit);

	UGaussian* GoToAmmo = NewObject<UGaussian>();
	GoToAmmo->Set(
		"Ammo",
		MovingAction->LowerBound,
		MovingAction->UpperBound,
		100,
		50
	);
	MovingAction->AddTerm(GoToAmmo->Name, GoToAmmo);

	UGaussian* Chase = NewObject<UGaussian>();
	Chase->Set(
		"Chase",
		MovingAction->LowerBound,
		MovingAction->UpperBound,
		150,
		50
	);
	MovingAction->AddTerm(Chase->Name, Chase);

}

void AFuzzyAIController::GenerateRule()
{
}

void AFuzzyAIController::SetActionRuleBlock()
{
	ActionRuleBlock->SetAccumulation(Accumulation);

	// Shoot Block
	URule* Shoot1Rule = NewObject<URule>();
	USequence* Shoot1Antecedent = NewObject<USequence>();

	TMap<UVariable*, UTerm*> Shoot1Condition;
	Shoot1Condition.Add(Health, HedgeNot->Compute(Health->GetTermFromMapByName("Low")));
	Shoot1Condition.Add(Ammo, HedgeNot->Compute(Ammo->GetTermFromMapByName("Low")));
	
	Shoot1Antecedent->Set(Shoot1Condition, Aggregation);
	Shoot1Rule->Set(Shoot1Antecedent, Action->GetTermFromMapByName("Shoot"), Activation);
	ActionRuleBlock->AddRuleToList(Shoot1Rule);

	// Run Block
	URule* Run1Rule = NewObject<URule>();
	USequence* Run1Antecedent = NewObject<USequence>();

	TMap<UVariable*, UTerm*> Run1Condition;
	Run1Condition.Add(Health, HedgeApprox->Compute(Health->GetTermFromMapByName("Low")));

	Run1Antecedent->Set(Run1Condition, Aggregation);
	Run1Rule->Set(Run1Antecedent, Action->GetTermFromMapByName("Run"), Activation);
	ActionRuleBlock->AddRuleToList(Run1Rule);

	URule* Run2Rule = NewObject<URule>();
	USequence* Run2Antecedent = NewObject<USequence>();

	TMap<UVariable*, UTerm*> Run2Condition;
	Run2Condition.Add(Ammo, HedgeApprox->Compute(Ammo->GetTermFromMapByName("Low")));

	Run2Antecedent->Set(Run2Condition, Aggregation);
	Run2Rule->Set(Run2Antecedent, Action->GetTermFromMapByName("Run"), Activation);
	ActionRuleBlock->AddRuleToList(Run2Rule);

}

void AFuzzyAIController::SetMovingRuleBlock()
{
}

void AFuzzyAIController::ResetReactionTimer()
{
	GetWorldTimerManager().SetTimer(ReactionTimer, this, &AFuzzyAIController::BeginReacting, ReactionTime, true);

}

void AFuzzyAIController::BeginReacting()
{
	AAgentCharacter* ControlledAgent = Cast<AAgentCharacter>(GetCharacter());
	if (ControlledAgent)
	{
		TMap<UVariable*, int32> ActionInput;
		ActionInput.Add(Health, ControlledAgent->CurrentHealth);
		ActionInput.Add(Ammo, ControlledAgent->CurrentAmmo);

		UTerm* AccumulatedAction = ActionRuleBlock->Accumulate(ActionInput);
		int32 DefuzzActionValue = Defuzzification->Defuzzify(AccumulatedAction);
		FString ActionName = Action->GetTermWithValue(DefuzzActionValue);
		float ActionDegree = Action->LastValue[ActionName];

		FString MovingName = MovingAction->GetTermWithValue(0);

		UpdateCharacter(ActionName, ActionDegree, MovingName);
	}

}

void AFuzzyAIController::UpdateCharacter(FString ActionState, float ActionDegree, FString MovingState)
{
	AAgentCharacter* ControlledAgent = Cast<AAgentCharacter>(GetCharacter());
	if (ControlledAgent)
	{
		if (ActionState == "Shoot")
		{
			ControlledAgent->SetShootingState();
			ControlledAgent->UpdateShootingRate(ActionDegree);
		}
		else if (ActionState == "Run")
		{
			ControlledAgent->SetRunningState();
			ControlledAgent->UpdateRunningSpeed(ActionDegree);
		}
		else
		{
			return;
		}

		if (MovingState == "Chase")
		{
			ControlledAgent->SetChaseState();
		}
		else if (MovingState == "Ammo")
		{
			ControlledAgent->SetAmmoState();
		}
		else if (MovingState == "MedKit")
		{
			ControlledAgent->SetMedKitState();
		}
		else if (MovingState == "Hide")
		{
			ControlledAgent->SetHideState();
		}
		else
		{
			return;
		}
	}

}
