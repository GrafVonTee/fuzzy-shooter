// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"

#include "Term/Term.h"

#include "Activation.generated.h"

/**
 * 
 */
UCLASS()
class FUZZYLIBRARY_API UActivation : public UObject
{
	GENERATED_BODY()
	
public:
	virtual UTerm* GetActivatedSet(float ActivationCoeff, UTerm* OriginalSet);

};
