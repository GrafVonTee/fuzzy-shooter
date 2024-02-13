// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"
#include "AgentCharacter.generated.h"


UENUM(BlueprintType)
enum class EActionState : uint8
{
	VE_Shoot	UMETA(DisplayName = "Shoot"),
	VE_Run		UMETA(DisplayName = "Run"),

	VE_Max		UMETA(Hidden)
};

UENUM(BlueprintType)
enum class EMovingState : uint8
{
	VE_Chase	UMETA(DisplayName = "Chase"),
	VE_Pose		UMETA(DisplayName = "Pose"),
	VE_Ammo		UMETA(DisplayName = "Go to Ammo"),
	VE_MedKit	UMETA(DisplayName = "Go to Medical Kit"),
	VE_Hide		UMETA(DisplayName = "Hide"),

	VE_Max		UMETA(Hidden)
};


/**
 * 
 */
UCLASS()
class FUZZYSHOOTER_API AAgentCharacter : public ABaseCharacter
{
	GENERATED_BODY()
	
public:
	// Sets default values for this character's properties
	AAgentCharacter();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Behaviour")
	EActionState ActionState;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Behaviour")
	EMovingState MovingState;
};
