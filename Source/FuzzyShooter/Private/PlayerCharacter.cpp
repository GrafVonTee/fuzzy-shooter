// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &Super::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &Super::MoveRight);
	PlayerInputComponent->BindAction("Shoot", IE_Pressed, this, &Super::Shoot);
	PlayerInputComponent->BindAction("Shoot", IE_Released, this, &Super::StopShooting);
}