// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FuzzyLib/Aggregation/Aggregation.h"
#include "MinAggregation.generated.h"

/**
 * 
 */
UCLASS()
class FUZZYSHOOTER_API UMinAggregation : public UAggregation
{
	GENERATED_BODY()
	
public:
	virtual float Compute(TArray<float> Values) override;

};
