// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"

#include "FuzzyLib/Rule/Sequence.h"
#include "FuzzyLib/Term/Term.h"
#include "FuzzyLib/Activation/Activation.h"

#include "Rule.generated.h"

/**
 * 
 */
UCLASS()
class FUZZYSHOOTER_API URule : public UObject
{
	GENERATED_BODY()
	
public:
	USequence* Antecedent;
	UTerm* Consequent;
	UActivation* Activation;

	UTerm* Activate(TMap<UVariable*, int32> Input);

	void Set(USequence* AntecedentOther, UTerm* ConsequentOther, UActivation* ActivationOther);
	
};
