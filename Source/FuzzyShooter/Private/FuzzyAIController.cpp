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
#include "FuzzyLib/Defuzzification/LargeMaxDefuzzification.h"

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

	RuleParser = NewObject<URuleParser>();

	SetHealthVariable();
	SetAmmoVariable();
	SetActionVariable();
	SetMovingActionVariable();

	SetRuleParser();

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
	Health->AddTerm(HealthLow->Name, HealthLow, 1);

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
	Health->AddTerm(HealthEnough->Name, HealthEnough, 1);

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
	Health->AddTerm(HealthMany->Name, HealthMany, 1);
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
	Ammo->AddTerm(AmmoLow->Name, AmmoLow, 1);

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
	Ammo->AddTerm(AmmoEnough->Name, AmmoEnough, 1);

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
	Ammo->AddTerm(AmmoMany->Name, AmmoMany, 1);

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
		30
	);
	Action->AddTerm(Run->Name, Run, 2);

	UGaussian* Shoot = NewObject<UGaussian>();
	Shoot->Set(
		"Shoot",
		Action->LowerBound,
		Action->UpperBound,
		100,
		30
	);
	Action->AddTerm(Shoot->Name, Shoot, 1);

}

void AFuzzyAIController::SetMovingActionVariable()
{
	MovingAction->Set("MovingAction", 0, 150, Receiver);

	UGaussian* Hide = NewObject<UGaussian>();
	Hide->Set(
		"Hide",
		MovingAction->LowerBound,
		MovingAction->UpperBound,
		0,
		30
	);
	MovingAction->AddTerm(Hide->Name, Hide, 2);

	UGaussian* GoToMedKit = NewObject<UGaussian>();
	GoToMedKit->Set(
		"GoToMedKit",
		MovingAction->LowerBound,
		MovingAction->UpperBound,
		50,
		30
	);
	MovingAction->AddTerm(GoToMedKit->Name, GoToMedKit, 1);

	UGaussian* GoToAmmo = NewObject<UGaussian>();
	GoToAmmo->Set(
		"GoToAmmo",
		MovingAction->LowerBound,
		MovingAction->UpperBound,
		100,
		30
	);
	MovingAction->AddTerm(GoToAmmo->Name, GoToAmmo, 1);

	UGaussian* Chase = NewObject<UGaussian>();
	Chase->Set(
		"Chase",
		MovingAction->LowerBound,
		MovingAction->UpperBound,
		150,
		30
	);
	MovingAction->AddTerm(Chase->Name, Chase, 4);

}

void AFuzzyAIController::SetRuleParser()
{
	TMap<FString, UVariable*> VarList;
	TMap<FString, UHedge*> HedgeList;

	VarList.Add("Health", Health);
	VarList.Add("Ammo", Ammo);
	VarList.Add("Action", Action);
	VarList.Add("MovingAction", MovingAction);

	HedgeList.Add("", NewObject<UHedge>());
	HedgeList.Add("Not", NewObject<UHedgeNot>());
	HedgeList.Add("Very", NewObject<UHedgeVery>());
	HedgeList.Add("Approximately", NewObject<UHedgeApproximately>());

	RuleParser->Set(VarList, HedgeList, Aggregation, Activation);

}

void AFuzzyAIController::SetActionRuleBlock()
{
	ActionRuleBlock->SetAccumulation(Accumulation);

	// Shoot Block
	URule* Shoot1Rule = RuleParser->ParseRule(
		"IF Health IS Not Approximately Low AND Ammo IS Not Low THEN Action IS Shoot"
	);

	ActionRuleBlock->AddRuleToList(Shoot1Rule);

	// Run Block
	URule* Run1Rule = RuleParser->ParseRule(
		"IF Health IS Approximately Low THEN Action IS Run"
	);
	URule* Run2Rule = RuleParser->ParseRule(
		"IF Ammo IS Approximately Low THEN Action IS Run"
	);

	ActionRuleBlock->AddRuleToList(Run1Rule);
	ActionRuleBlock->AddRuleToList(Run2Rule);

}

void AFuzzyAIController::SetMovingRuleBlock()
{
	MovingRuleBlock->SetAccumulation(Accumulation);

	// Chase Block
	URule* ChaseRule = RuleParser->ParseRule(
		"IF Health IS Not Low AND Ammo IS Not Low THEN MovingAction IS Chase"
	);
	MovingRuleBlock->AddRuleToList(ChaseRule);

	// GoToAmmo Block
	URule* GoToAmmoRule = RuleParser->ParseRule(
		"IF Health IS Not Low AND Ammo IS Not Many THEN MovingAction IS GoToAmmo"
	);
	MovingRuleBlock->AddRuleToList(GoToAmmoRule);

	// GoToMedKit Block
	URule* GoToMedKitRule = RuleParser->ParseRule(
		"IF Health IS Not Many AND Health IS Not Very Low THEN MovingAction IS GoToMedKit"
	);
	MovingRuleBlock->AddRuleToList(GoToMedKitRule);

	// Hide Block
	URule* HideRule1 = RuleParser->ParseRule(
		"IF Health IS Very Low THEN MovingAction IS Hide"
	);
	URule* HideRule2 = RuleParser->ParseRule(
		"IF Health IS Low AND Ammo IS Low THEN MovingAction IS Hide"
	);
	MovingRuleBlock->AddRuleToList(HideRule1);
	MovingRuleBlock->AddRuleToList(HideRule2);

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

		UTerm* AccumulatedMoving = MovingRuleBlock->Accumulate(ActionInput);
		int32 DefuzzMovingValue = NewObject<ULargeMaxDefuzzification>()->Defuzzify(AccumulatedMoving);
		FString MovingName = MovingAction->GetTermWithValue(DefuzzMovingValue);

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
			ControlledAgent->UpdateShootingRate(ActionDegree);
			ControlledAgent->SetShootingState();
		}
		else if (ActionState == "Run")
		{
			ControlledAgent->UpdateRunningSpeed(ActionDegree);
			ControlledAgent->SetRunningState();
		}
		else
		{
			return;
		}

		if (MovingState == "Chase")
		{
			ControlledAgent->SetChaseState();
		}
		else if (MovingState == "GoToAmmo")
		{
			ControlledAgent->SetAmmoState();
		}
		else if (MovingState == "GoToMedKit")
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
