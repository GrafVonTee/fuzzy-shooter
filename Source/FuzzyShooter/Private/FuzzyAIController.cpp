// Fill out your copyright notice in the Description page of Project Settings.


#include "FuzzyAIController.h"
#include "UObject/NameTypes.h"

#include "FuzzyLib/Term/Triangluar.h"
#include "FuzzyLib/Term/Trapezoid.h"

#include "AgentCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/EngineTypes.h"

void SetHealthVariable(UVariable* Health)
{
	Health->Set("Health", 0, 150);

	UTrapezoid* HealthLow = NewObject<UTrapezoid>();
	HealthLow->Set(
		"Low",
		Health->LowerBound,
		Health->UpperBound,
		0,
		0,
		40,
		60
	);
	Health->AddTerm(HealthLow->Name.ToString(), HealthLow);

	UTrapezoid* HealthEnough = NewObject<UTrapezoid>();
	HealthEnough->Set(
		"Enough",
		Health->LowerBound,
		Health->UpperBound,
		40,
		60,
		90,
		110
	);
	Health->AddTerm(HealthEnough->Name.ToString(), HealthEnough);

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
	Health->AddTerm(HealthMany->Name.ToString(), HealthMany);
}

void SetAmmoVariable(UVariable* Ammo)
{
	Ammo->Set("Ammo", 0, 150);
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
	Ammo->AddTerm(AmmoLow->Name.ToString(), AmmoLow);

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
	Ammo->AddTerm(AmmoEnough->Name.ToString(), AmmoEnough);

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
	Ammo->AddTerm(AmmoMany->Name.ToString(), AmmoMany);

}

void SetActionVariable(UVariable* Action)
{
	Action->Set("Action", 0, 100);

	UTriangluar* Run = NewObject<UTriangluar>();
	Run->Set(
		"Run",
		Action->LowerBound,
		Action->UpperBound,
		0,
		0,
		100
	);
	Action->AddTerm(Run->Name.ToString(), Run);

	UTriangluar* Shoot = NewObject<UTriangluar>();
	Run->Set(
		"Shoot",
		Action->LowerBound,
		Action->UpperBound,
		0,
		100,
		100
	);
	Action->AddTerm(Shoot->Name.ToString(), Shoot);

}

void SetMovingActionVariable(UVariable* MovingAction)
{
	MovingAction->Set("Moving Action", 0, 150);

	UTriangluar* Hide = NewObject<UTriangluar>();
	Hide->Set(
		"Hide",
		MovingAction->LowerBound,
		MovingAction->UpperBound,
		0,
		0,
		50
	);
	MovingAction->AddTerm(Hide->Name.ToString(), Hide);

	UTriangluar* GoToMedKit = NewObject<UTriangluar>();
	GoToMedKit->Set(
		"MedKit",
		MovingAction->LowerBound,
		MovingAction->UpperBound,
		0,
		50,
		100
	);
	MovingAction->AddTerm(GoToMedKit->Name.ToString(), GoToMedKit);

	UTriangluar* GoToAmmo = NewObject<UTriangluar>();
	GoToAmmo->Set(
		"Ammo",
		MovingAction->LowerBound,
		MovingAction->UpperBound,
		50,
		100,
		150
	);
	MovingAction->AddTerm(GoToAmmo->Name.ToString(), GoToAmmo);

	UTriangluar* Chase = NewObject<UTriangluar>();
	Chase->Set(
		"Chase",
		MovingAction->LowerBound,
		MovingAction->UpperBound,
		100,
		150,
		150
	);
	MovingAction->AddTerm(Chase->Name.ToString(), Chase);

}

void AFuzzyAIController::BeginPlay()
{
	Super::BeginPlay();

	SetHealthVariable(Health);
	SetAmmoVariable(Ammo);
	SetActionVariable(Action);
	SetMovingActionVariable(MovingAction);

	Action->UpdateDegreeOfMembership(100);
	MovingAction->UpdateDegreeOfMembership(150);
}

AFuzzyAIController::AFuzzyAIController()
{
	Health = NewObject<UVariable>();
	Ammo = NewObject<UVariable>();
	Action = NewObject<UVariable>();
	MovingAction = NewObject<UVariable>();

}

void AFuzzyAIController::ResetReactionTimer()
{
	GetWorldTimerManager().SetTimer(ReactionTimer, this, &AFuzzyAIController::BeginReacting, ReactionTime, true);

}

void AFuzzyAIController::BeginReacting()
{
}

void AFuzzyAIController::UpdateCharacter()
{
	ACharacter* ControlledAgent = GetCharacter();
	if (ControlledAgent->IsA(AAgentCharacter::StaticClass()))
	{
	}
}
