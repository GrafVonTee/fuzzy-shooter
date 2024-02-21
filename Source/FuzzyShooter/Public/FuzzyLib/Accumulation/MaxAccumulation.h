// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FuzzyLib/Accumulation/Accumulation.h"
#include "MaxAccumulation.generated.h"

/**
 * 
 */
UCLASS()
class FUZZYSHOOTER_API UMaxAccumulation : public UAccumulation
{
	GENERATED_BODY()
	
public:
	virtual UTerm* Compute(TArray<UTerm*> TermList) override;

};
