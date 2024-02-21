// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"

#include "FuzzyLib/Term/Term.h"

#include "Accumulation.generated.h"

/**
 * 
 */
UCLASS()
class FUZZYSHOOTER_API UAccumulation : public UObject
{
	GENERATED_BODY()
	
public:
	virtual UTerm* Compute(TArray<UTerm*> TermList);

};
