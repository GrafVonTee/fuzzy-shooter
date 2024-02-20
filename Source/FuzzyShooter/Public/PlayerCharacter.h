// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"
#include "PlayerCharacter.generated.h"

/**
 * 
 */
UCLASS()
class FUZZYSHOOTER_API APlayerCharacter : public ABaseCharacter
{
	GENERATED_BODY()

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
public:
	void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

};
