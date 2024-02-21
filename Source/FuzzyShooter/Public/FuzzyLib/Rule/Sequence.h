// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"

#include "FuzzyLib/Variable/Variable.h"
#include "FuzzyLib/Aggregation/Aggregation.h"

#include "Sequence.generated.h"

/**
 * 
 */
UCLASS()
class FUZZYSHOOTER_API USequence : public UObject
{
	GENERATED_BODY()
	
public:
	UPROPERTY()
	TMap<UVariable*, UTerm*> Content;

	UPROPERTY()
	UAggregation* Aggregation;

	float Compute(TMap<UVariable*, int32> Input);

	void Set(TMap<UVariable*, UTerm*> ContentOther, UAggregation* AggregationOther);

};
