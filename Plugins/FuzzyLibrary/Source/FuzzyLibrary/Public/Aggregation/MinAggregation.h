// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Aggregation.h"
#include "MinAggregation.generated.h"

/**
 * 
 */
UCLASS()
class FUZZYLIBRARY_API UMinAggregation : public UAggregation
{
	GENERATED_BODY()
	
public:
	UFUNCTION()
	virtual float Compute(TArray<float> Values) override;

};
