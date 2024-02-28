// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Accumulation.h"
#include "MaxAccumulation.generated.h"

/**
 * 
 */
UCLASS()
class FUZZYLIBRARY_API UMaxAccumulation : public UAccumulation
{
	GENERATED_BODY()
	
public:
	virtual UTerm* Compute(TArray<UTerm*> TermList) override;

};
