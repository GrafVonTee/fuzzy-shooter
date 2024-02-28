// Fill out your copyright notice in the Description page of Project Settings.


#include "Aggregation/MinAggregation.h" 	
#include "Kismet/KismetMathLibrary.h"

float UMinAggregation::Compute(TArray<float> Values)
{
	int32 IndexMinValue;
	float MinValue;
	UKismetMathLibrary::MinOfFloatArray(Values, IndexMinValue, MinValue);

	return MinValue;
}
