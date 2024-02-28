// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Hedge.h"
#include "HedgeVery.generated.h"

/**
 * 
 */
UCLASS()
class FUZZYLIBRARY_API UHedgeVery : public UHedge
{
	GENERATED_BODY()
	
public:
	virtual UTerm* Compute(UTerm* OriginalSet) override;

};
