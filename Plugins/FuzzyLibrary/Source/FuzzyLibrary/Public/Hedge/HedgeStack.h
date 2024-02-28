// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"

#include "Hedge.h"

#include "HedgeStack.generated.h"

/**
 * 
 */
UCLASS()
class FUZZYLIBRARY_API UHedgeStack : public UObject
{
	GENERATED_BODY()
	
	UPROPERTY()
	TArray<UHedge*> Stack;

public:
	void Clear();

	void Add(UHedge* NewHedge);

	UTerm* Compute(UTerm* Term);
};
