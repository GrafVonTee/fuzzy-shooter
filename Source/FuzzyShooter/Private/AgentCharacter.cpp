// Fill out your copyright notice in the Description page of Project Settings.


#include "AgentCharacter.h"
#include "Engine/EngineTypes.h"

void AAgentCharacter::BeginPlay()
{
	Super::BeginPlay();

	SetShootingState();
	MovingState = EMovingState::VE_Chase;

}

void AAgentCharacter::SetShootingState()
{
	ActionState = EActionState::VE_Shoot;
	ResetShootingTimer();

}

void AAgentCharacter::SetRunningState()
{
	ActionState = EActionState::VE_Run;
	ClearShootingTimer();

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
