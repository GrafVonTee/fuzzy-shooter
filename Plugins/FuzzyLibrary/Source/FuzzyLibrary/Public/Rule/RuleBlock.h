// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"

#include "Rule.h"
#include "Accumulation/Accumulation.h"

#include "RuleBlock.generated.h"

/**
 * 
 */
UCLASS()
class FUZZYLIBRARY_API URuleBlock : public UObject
{
	GENERATED_BODY()
	
public:
	UPROPERTY()
	TArray<URule*> RuleList;

	UPROPERTY()
	UAccumulation* Accumulation;

	void AddRuleToList(URule* Rule);

	void SetAccumulation(UAccumulation* AccumulationOther);

	UTerm* Accumulate(TMap<UVariable*, int32> Input);

};
