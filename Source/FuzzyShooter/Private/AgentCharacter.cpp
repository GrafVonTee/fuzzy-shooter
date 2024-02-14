// Fill out your copyright notice in the Description page of Project Settings.


#include "AgentCharacter.h"
#include "PlayerCharacter.h"
#include "DefaultConsumed.h"
#include "Obstacle.h"
#include "InterestPointInterface.h"
#include "Engine/EngineTypes.h"
#include "Kismet/GameplayStatics.h"

void AAgentCharacter::BeginPlay()
{
	Super::BeginPlay();

	SetShootingState();
	SetChaseState();

	ResetMovingTimer();

}

void AAgentCharacter::SwapActionState()
{
	static EActionState LastActionState = ActionState;

	if (ActionState != LastActionState)
	{
		switch (ActionState)
		{
		case EActionState::VE_Shoot:
			UpdateShootingRate(1);
			SetShootingState();
			break;

		case EActionState::VE_Run:
			UpdateRunningSpeed(1);
			SetRunningState();
			break;

		default:
			break;
		}

		LastActionState = ActionState;
	}

}

void AAgentCharacter::SwapMovingState()
{
	static EMovingState LastMovingState = MovingState;

	if (MovingState != LastMovingState)
	{
		switch (MovingState)
		{
		case EMovingState::VE_Chase:
			SetChaseState();
			break;

		case EMovingState::VE_Ammo:
			SetAmmoState();
			break;

		case EMovingState::VE_MedKit:
			SetMedKitState();
			break;

		case EMovingState::VE_Hide:
			SetHideState();
			break;

		default:
			break;
		}

		LastMovingState = MovingState;
		ResetMovingTimer();
	}

}

void AAgentCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	SwapActionState();
	SwapMovingState();
}

void AAgentCharacter::SetShootingState()
{
	ActionState = EActionState::VE_Shoot;
	ResetShootingTimer();
	UpdateRunningSpeed(0);

}

void AAgentCharacter::UpdateShootingRate(float Degree)
{
	if (Degree == 0)
	{
		CurrentShootRate = 0;
	}
	else
	{
		CurrentShootRate = MaximumShootRate + (MinimumShootRate - MaximumShootRate) * (1 - Degree);
	}

}

void AAgentCharacter::SetRunningState()
{
	ActionState = EActionState::VE_Run;
	ClearShootingTimer();
	UpdateShootingRate(0);

}

void AAgentCharacter::UpdateRunningSpeed(float Degree)
{
	CurrentSpeed = BaseSpeed + (BoostMaxSpeed - BaseSpeed) * Degree;

}

void AAgentCharacter::SetChaseState()
{
	MovingState = EMovingState::VE_Chase;
	InterestPoint = Cast<AActor>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));

}

void AAgentCharacter::SetNewPointInterest()
{
	InterestPoint = ActorsArray[0];
	IInterestPointInterface* InterfaceRef = Cast<IInterestPointInterface>(InterestPoint);

	if (!InterfaceRef)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s"), *(InterestPoint->GetName()));
		InterestPoint = nullptr;
		return;
	}

	float MinimumDistance = FVector::Dist(GetActorLocation(), InterfaceRef->Execute_GetPointOfInterest(InterestPoint));

	for (AActor* Actor : ActorsArray)
	{
		InterfaceRef = Cast<IInterestPointInterface>(Actor);
		float Distance = FVector::Dist(GetActorLocation(), InterfaceRef->Execute_GetPointOfInterest(Actor));

		if (Distance < MinimumDistance)
		{
			InterestPoint = Actor;
			MinimumDistance = Distance;
		}
	}

}

void AAgentCharacter::SetAmmoState()
{
	MovingState = EMovingState::VE_Ammo;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AmmoBoxClass, ActorsArray);
	SetNewPointInterest();

	ActorsArray.Empty();

}

void AAgentCharacter::SetMedKitState()
{
	MovingState = EMovingState::VE_MedKit;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), MedKitClass, ActorsArray);
	SetNewPointInterest();

	ActorsArray.Empty();

}

void AAgentCharacter::SetHideState()
{
	MovingState = EMovingState::VE_Hide;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ObstacleClass, ActorsArray);
	SetNewPointInterest();

	ActorsArray.Empty();

}

void AAgentCharacter::OneShot()
{
	Shoot();
	StopShooting();

}

void AAgentCharacter::ResetMovingTimer()
{
	GetWorldTimerManager().SetTimer(MovingTimerHandle, this, &AAgentCharacter::MoveToInterestPoint, PathFindDuration, true);

}

void AAgentCharacter::ResetShootingTimer()
{
	GetWorldTimerManager().SetTimer(ShootingTimerHandle, this, &AAgentCharacter::OneShot, CurrentShootRate, true);

}

void AAgentCharacter::ClearShootingTimer()
{
	GetWorldTimerManager().ClearTimer(ShootingTimerHandle);

}
