// Fill out your copyright notice in the Description page of Project Settings.


#include "AgentCharacter.h"

void AAgentCharacter::ReceiveDamage(int32 DamageTaken)
{
	Super::ReceiveDamage(DamageTaken);

	if (bIsDead)
	{
		Destroy();
	}

}