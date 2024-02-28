// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"

#include "Sequence.h"
#include "Term/Term.h"
#include "Activation/Activation.h"

#include "Rule.generated.h"

/**
 * 
 */
UCLASS()
class FUZZYLIBRARY_API URule : public UObject
{
	GENERATED_BODY()
	
public:
	UPROPERTY()
	USequence* Antecedent;

	UPROPERTY()
	UTerm* Consequent;
	
	UPROPERTY()
	UActivation* Activation;

	UTerm* Activate(TMap<UVariable*, int32> Input);

	void Set(USequence* AntecedentOther, UTerm* ConsequentOther, UActivation* ActivationOther);
	
};
