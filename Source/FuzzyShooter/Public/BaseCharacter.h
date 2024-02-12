// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BaseCharacter.generated.h"

UCLASS()
class FUZZYSHOOTER_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseCharacter();

	// Health Block
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	int32 CurrentHealth = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	int32 MaxHealth = 150;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	int32 RegenRate = 3; // seconds

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	int32 RegenValue = 10;

	// Ammo Block
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ammo")
	int32 CurrentAmmo = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ammo")
	int32 MaxAmmo = 150;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ammo")
	int32 CurrentShootRate = 3; // times per second

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ammo")
	int32 MaximumShootRate = 10; // times per second

	// Speed Block
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Speed")
	float CurrentSpeed = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Speed")
	float BaseSpeed = 400;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Speed")
	float BoostMaxSpeed = 1000;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Speed")
	bool bIsOnBoost = false;

	// Control Block
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Control")
	bool bIsDead = false;

	/** Movement Function Section */
	void MoveForward(float Axis);
	void MoveRight(float Axis);

	/** Shoot functions */
	void Shoot();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
