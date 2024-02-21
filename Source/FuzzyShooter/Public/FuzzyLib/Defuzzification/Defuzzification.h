// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"

#include "FuzzyLib/Term/Term.h"

#include "Defuzzification.generated.h"

/**
 * 
 */
UCLASS()
class FUZZYSHOOTER_API UDefuzzification : public UObject
{
	GENERATED_BODY()
	
public:
	virtual int32 Defuzzify(UTerm* Term);

};
