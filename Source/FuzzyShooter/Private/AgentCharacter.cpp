// Fill out your copyright notice in the Description page of Project Settings.


#include "AgentCharacter.h"
#include "PlayerCharacter.h"
#include "DefaultConsumed.h"
#include "Obstacle.h"
#include "InterestPointInterface.h"
#include "Engine/EngineTypes.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/CharacterMovementComponent.h"

void AAgentCharacter::BeginPlay()
{
	Super::BeginPlay();

	SetShootingState();
	SetChaseState();

	ResetMovingTimer();

}

//void AAgentCharacter::SwapActionState()
//{
//	static EActionState LastActionState = ActionState;
//
//	if (ActionState != LastActionState)
//	{
//		switch (ActionState)
//		{
//		case EActionState::VE_Shoot:
//			UpdateShootingRate(1);
//			SetShootingState();
//			break;
//
//		case EActionState::VE_Run:
//			UpdateRunningSpeed(1);
//			SetRunningState();
//			break;
//
//		default:
//			break;
//		}
//
//		LastActionState = ActionState;
//	}
//
//}

//void AAgentCharacter::SwapMovingState()
//{
//	static EMovingState LastMovingState = MovingState;
//
//	if (MovingState != LastMovingState)
//	{
//		switch (MovingState)
//		{
//		case EMovingState::VE_Chase:
//			SetChaseState();
//			break;
//
//		case EMovingState::VE_Ammo:
//			SetAmmoState();
//			break;
//
//		case EMovingState::VE_MedKit:
//			SetMedKitState();
//			break;
//
//		case EMovingState::VE_Hide:
//			SetHideState();
//			break;
//
//		default:
//			break;
//		}
//
//		LastMovingState = MovingState;
//		ResetMovingTimer();
//	}
//
//}

void AAgentCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//SwapActionState();
	//SwapMovingState();
}

void AAgentCharacter::SetShootingState()
{
	ActionState = EActionState::VE_Shoot;
	ResetShootingTimer();
	OneShot();
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
	GetCharacterMovement()->MaxWalkSpeed = CurrentSpeed;
}

void AAgentCharacter::SetChaseState()
{
	MovingState = EMovingState::VE_Chase;
	InterestPoint = Cast<AActor>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));

}

void AAgentCharacter::SetNewPointInterest()
{
	if (ActorsArray.Num() == 0)
	{
		InterestPoint = nullptr;
		return;
	}

	InterestPoint = ActorsArray[0];
	IInterestPointInterface* InterfaceRef = Cast<IInterestPointInterface>(InterestPoint);

	if (!InterfaceRef)
	{
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

void AAgentCharacter::UpdatePointOfInterest()
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
}

void AAgentCharacter::SetAmmoState()
{
	ActorsArray.Empty();

	MovingState = EMovingState::VE_Ammo;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AmmoBoxClass, ActorsArray);
	SetNewPointInterest();

}

void AAgentCharacter::SetMedKitState()
{
	ActorsArray.Empty();

	MovingState = EMovingState::VE_MedKit;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), MedKitClass, ActorsArray);
	SetNewPointInterest();

}

void AAgentCharacter::SetHideState()
{
	ActorsArray.Empty();

	MovingState = EMovingState::VE_Hide;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ObstacleClass, ActorsArray);
	SetNewPointInterest();

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
