// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FuzzyLib/Defuzzification/Defuzzification.h"
#include "CentroidDefuzzification.generated.h"

/**
 * 
 */
UCLASS()
class FUZZYSHOOTER_API UCentroidDefuzzification : public UDefuzzification
{
	GENERATED_BODY()

public:
	virtual int32 Defuzzify(UTerm* Term) override;

};
