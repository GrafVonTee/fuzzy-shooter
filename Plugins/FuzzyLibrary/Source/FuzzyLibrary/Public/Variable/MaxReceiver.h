// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "VariableReceiver.h"
#include "MaxReceiver.generated.h"

/**
 * 
 */
UCLASS()
class FUZZYLIBRARY_API UMaxReceiver : public UVariableReceiver
{
	GENERATED_BODY()
	
public:
	virtual FString Receive(TMap<FString, float> List) override;

};
