// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "SNorm.generated.h"

/**
 * 
 */
UCLASS()
class FUZZYLIBRARY_API USNorm : public UObject
{
	GENERATED_BODY()
	
public:
	virtual float Compute(float a, float b);

};
