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

	void SetNewPointInterest();

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	/** Action Behaviour Section */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Action Behaviour")
	EActionState ActionState;

	void SwapActionState();

	UFUNCTION(BlueprintCallable, Category = "Action Behaviour")
	void SetShootingState();

	UFUNCTION(BlueprintCallable, Category = "Shooting Control")
	void UpdateShootingRate(float Degree);

	UFUNCTION(BlueprintCallable, Category = "Action Behaviour")
	void SetRunningState();

	UFUNCTION(BlueprintCallable, Category = "Running Control")
	void UpdateRunningSpeed(float Degree);


	/** Moving Behaviour Section */
	FTimerHandle MovingTimerHandle;
	const float PathFindDuration = 0.25;

	UFUNCTION(BlueprintCallable, Category = "Moving Behaviour")
	void ResetMovingTimer();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Moving Behaviour")
	EMovingState MovingState;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Moving Behaviour")
	AActor* InterestPoint;

	void SwapMovingState();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Moving Behaviour")
	void MoveToInterestPoint();

	UFUNCTION(BlueprintCallable, Category = "Moving Behaviour")
	void SetChaseState();

	UFUNCTION(BlueprintCallable, Category = "Moving Behaviour")
	void SetAmmoState();

	UFUNCTION(BlueprintCallable, Category = "Moving Behaviour")
	void SetMedKitState();
	
	UFUNCTION(BlueprintCallable, Category = "Moving Behaviour")
	void SetHideState();


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
	float MaximumShootRate = 0.2; // seconds

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shooting")
	float MinimumShootRate = 2; // seconds


	/** Garbage Section */
	UPROPERTY()  // Put this in the header file so you can mark it as UPROPERTY
	TArray<AActor*> ActorsArray; // Without UPROPERTY, strange things may happen with garbage collection on TArray

	UPROPERTY(EditDefaultsOnly, Category = "Interest Points")
	TSubclassOf<class ADefaultConsumed> AmmoBoxClass;

	UPROPERTY(EditDefaultsOnly, Category = "Interest Points")
	TSubclassOf<class ADefaultConsumed> MedKitClass;

	UPROPERTY(EditDefaultsOnly, Category = "Interest Points")
	TSubclassOf<class AObstacle> ObstacleClass;
};
