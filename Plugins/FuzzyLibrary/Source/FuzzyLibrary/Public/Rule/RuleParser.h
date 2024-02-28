// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"

#include "Rule.h"
#include "Hedge/Hedge.h"
#include "Variable/Variable.h"

#include "RuleParser.generated.h"

/**
 * 
 */
UCLASS()
class FUZZYLIBRARY_API URuleParser : public UObject
{
	GENERATED_BODY()
	
public:
	UPROPERTY()
	TMap<FString, UVariable*> VarMap;

	UPROPERTY()
	TMap<FString, UHedge*> HedgeMap;

	UPROPERTY()
	UAggregation* Aggregation;

	UPROPERTY()
	UActivation* Activation;

	void Set(
		TMap<FString, UVariable*> VarList,
		TMap<FString, UHedge*> HedgeList,
		UAggregation* AggregationOther,
		UActivation* ActivationOther
	);

	URule* ParseRule(FString Input);

};
