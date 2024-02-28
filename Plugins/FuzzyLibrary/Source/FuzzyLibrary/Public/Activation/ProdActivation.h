// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Activation.h"
#include "ProdActivation.generated.h"

/**
 * 
 */
UCLASS()
class FUZZYLIBRARY_API UProdActivation : public UActivation
{
	GENERATED_BODY()
	
public:
	virtual UTerm* GetActivatedSet(float ActivationCoeff, UTerm* OriginalSet) override;

};
