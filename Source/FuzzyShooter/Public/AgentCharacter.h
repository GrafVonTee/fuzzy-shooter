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
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	/** Action Behaviour Section */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Action Behaviour")
	EActionState ActionState;

	UFUNCTION(BlueprintCallable, Category = "Action Behaviour")
	void SetShootingState();

	UFUNCTION(BlueprintCallable, Category = "Action Behaviour")
	void SetRunningState();


	/** Moving Behaviour Section */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Moving Behaviour")
	EMovingState MovingState;
	

	/** Shooting Section */
	void OneShot();

	FTimerHandle ShootingTimerHandle;

	UFUNCTION(BlueprintCallable, Category = "Shooting Control")
	void ResetShootingTimer();

	UFUNCTION(BlueprintCallable, Category = "Shooting Control")
	void ClearShootingTimer();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shooting")
	float CurrentShootRate = 1; // seconds

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shooting")
	float MaximumShootRate = 0.3; // seconds

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shooting")
	float MinimumShootRate = 2; // seconds
};
