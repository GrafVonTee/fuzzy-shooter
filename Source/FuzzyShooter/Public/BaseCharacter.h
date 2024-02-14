// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttackInterface.h"
#include "GameFramework/Character.h"
#include "BaseCharacter.generated.h"

UCLASS()
class FUZZYSHOOTER_API ABaseCharacter : public ACharacter, public IAttackInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseCharacter();

	/** Objects block */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Spawner")
	class USpringArmComponent* SpawnerSpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Spawner")
	class UStaticMeshComponent* SpawnPoint;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Health Block
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	int32 CurrentHealth = 150;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	int32 MaxHealth = 150;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	float RegenRate = 3; // seconds

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	int32 RegenValue = 5;

	void RegenHealth();

	FTimerHandle RegenTimerHandle;;
	void ResetRegenTimer();


	// Ammo Block
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ammo")
	int32 CurrentAmmo = 150;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ammo")
	int32 MaxAmmo = 150;


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

	UFUNCTION(BlueprintCallable, Category = "Control")
	virtual void ReceiveDamage(int32 DamageTaken);

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Control")
	void OnDestroyAction();


	/** Shooting section */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shooting")
	bool bShootBlocked = false;

	bool CanShoot() const;
	void Shoot();
	void StopShooting();


	/** Movement Function Section */
	void MoveForward(float Axis);
	void MoveRight(float Axis);

};
