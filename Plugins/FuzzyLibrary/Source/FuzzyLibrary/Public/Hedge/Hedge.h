// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"

#include "Term/Term.h"

#include "Hedge.generated.h"

/**
 * 
 */
UCLASS()
class FUZZYLIBRARY_API UHedge : public UObject
{
	GENERATED_BODY()
	
public:
	virtual UTerm* Compute(UTerm* OriginalSet);

};
