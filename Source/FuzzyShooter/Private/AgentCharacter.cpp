// Fill out your copyright notice in the Description page of Project Settings.


#include "AgentCharacter.h"

AAgentCharacter::AAgentCharacter()
{
	ActionState = EActionState::VE_Shoot;
	MovingState = EMovingState::VE_Chase;
}