// Fill out your copyright notice in the Description page of Project Settings.


#include "AgentCharacter.h"
#include "Engine/EngineTypes.h"

void AAgentCharacter::BeginPlay()
{
	Super::BeginPlay();

	SetShootingState();
	MovingState = EMovingState::VE_Chase;

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
}

void AAgentCharacter::SetPoseState()
{
}

void AAgentCharacter::SetAmmoState()
{
}

void AAgentCharacter::SetMedKitState()
{
}

void AAgentCharacter::SetHideState()
{
}

void AAgentCharacter::OneShot()
{
	Shoot();
	StopShooting();

}

void AAgentCharacter::ResetShootingTimer()
{
	GetWorldTimerManager().SetTimer(ShootingTimerHandle, this, &AAgentCharacter::OneShot, CurrentShootRate, true);

}

void AAgentCharacter::ClearShootingTimer()
{
	GetWorldTimerManager().ClearTimer(ShootingTimerHandle);

}
