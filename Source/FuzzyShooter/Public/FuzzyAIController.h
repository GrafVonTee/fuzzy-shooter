// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"

#include "FuzzyLib/Variable/Variable.h"
#include "FuzzyLib/Accumulation/Accumulation.h"
#include "FuzzyLib/Activation/Activation.h"
#include "FuzzyLib/Aggregation/Aggregation.h"
#include "FuzzyLib/Defuzzification/Defuzzification.h"
#include "FuzzyLib/Rule/RuleBlock.h"
#include "FuzzyLib/Term/Term.h"
#include "FuzzyLib/Rule/RuleParser.h"

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

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Timer")
	float ReactionTime = 1; // in sec

	UPROPERTY()
	FTimerHandle ReactionTimer;

	UFUNCTION(BlueprintCallable, Category = "Timer")
	void ResetReactionTimer();

	UFUNCTION(BlueprintCallable, Category = "General")
	void BeginReacting();

	UFUNCTION(BlueprintCallable, Category = "General")
	void UpdateCharacter(FString ActionState, float ActionDegree, FString MovingState);


	/** Fuzzy Logic Beginning */

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "General")
	UVariable* Health;

	void SetHealthVariable();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "General")
	UVariable* Ammo;

	void SetAmmoVariable();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "General")
	UVariable* Action;

	void SetActionVariable();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "General")
	UVariable* MovingAction;

	void SetMovingActionVariable();

	UPROPERTY()
	UAggregation* Aggregation;

	UPROPERTY()
	UActivation* Activation;
	
	UPROPERTY()
	UAccumulation* Accumulation;
	
	UPROPERTY()
	UVariableReceiver* Receiver;
	
	UPROPERTY()
	UDefuzzification* Defuzzification;

	UPROPERTY()
	URuleParser* RuleParser;

	void SetRuleParser();

	UPROPERTY()
	URuleBlock* ActionRuleBlock;

	void SetActionRuleBlock();

	UPROPERTY()
	URuleBlock* MovingRuleBlock;

	void SetMovingRuleBlock();

};
