// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Term/Term.h"
#include "Gaussian.generated.h"

/**
 * 
 */
UCLASS()
class FUZZYLIBRARY_API UGaussian : public UTerm
{
	GENERATED_BODY()
	
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Membership")
	float Mean;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Membership")
	float Dist;

	virtual void MakeRange() override;

	void Set(
		FString NameOther,
		int32 LowerBoundOther,
		int32 UpperBoundOther,
		float MeanOther,
		float DistOther
	);
};
