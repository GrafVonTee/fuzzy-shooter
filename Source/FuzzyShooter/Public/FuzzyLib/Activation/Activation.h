// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"

#include "FuzzyLib/Term/Term.h"

#include "Activation.generated.h"

/**
 * 
 */
UCLASS()
class FUZZYSHOOTER_API UActivation : public UObject
{
	GENERATED_BODY()
	
public:
	UActivation() = default;

	virtual UTerm* GetActivatedSet(float ActivationCoeff, UTerm* OriginalSet);

};
