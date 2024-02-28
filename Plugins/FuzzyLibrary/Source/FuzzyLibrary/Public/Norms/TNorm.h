// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "TNorm.generated.h"

/**
 * 
 */
UCLASS()
class FUZZYLIBRARY_API UTNorm : public UObject
{
	GENERATED_BODY()
	
public:
	static float Compute(float a, float b);

};
