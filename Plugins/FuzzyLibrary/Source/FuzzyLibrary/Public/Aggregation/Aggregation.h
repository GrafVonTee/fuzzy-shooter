// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Aggregation.generated.h"

/**
 * 
 */
UCLASS()
class FUZZYLIBRARY_API UAggregation : public UObject
{
	GENERATED_BODY()
	
public:
	virtual float Compute(TArray<float> Values);

};
