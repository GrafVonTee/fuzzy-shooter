// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"

#include "FuzzyLib/Term/Term.h"

#include "VariableReceiver.generated.h"

/**
 * 
 */
UCLASS()
class FUZZYSHOOTER_API UVariableReceiver : public UObject
{
	GENERATED_BODY()
	
public:
	virtual FString Receive(TMap<FString, float> List);

};
