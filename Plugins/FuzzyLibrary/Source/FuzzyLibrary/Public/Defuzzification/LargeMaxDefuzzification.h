// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Defuzzification.h"
#include "LargeMaxDefuzzification.generated.h"

/**
 * 
 */
UCLASS()
class FUZZYLIBRARY_API ULargeMaxDefuzzification : public UDefuzzification
{
	GENERATED_BODY()
	
public:
	virtual int32 Defuzzify(UTerm* Term) override;

};
