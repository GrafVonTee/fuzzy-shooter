// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"

#include "FuzzyLib/Variable/Variable.h"

#include "FuzzyAIController.generated.h"

/**
 * 
 */
UCLASS()
class FUZZYSHOOTER_API AFuzzyAIController : public AAIController
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;

public:
	AFuzzyAIController();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "General")
	UVariable* Health;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "General")
	UVariable* Ammo;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "General")
	UVariable* Action;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "General")
	UVariable* MovingAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Timer")
	float ReactionTime = 1; // in sec

	FTimerHandle ReactionTimer;

	UFUNCTION(BlueprintCallable, Category = "Timer")
	void ResetReactionTimer();

	UFUNCTION(BlueprintCallable, Category = "General")
	void BeginReacting();

	UFUNCTION(BlueprintCallable, Category = "General")
	void UpdateCharacter();
};
