// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Term.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class FUZZYSHOOTER_API UTerm : public UObject
{
	GENERATED_BODY()
	
public:
	UTerm();

	// Term constructor
	//UTerm(FName nameOther, int32 lowerBoundOther, int32 upperBoundOther);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "General")
	FName Name;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Range")
	int32 LowerBound;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Range")
	int32 UpperBound;

	UPROPERTY()
	TArray<float> ValueRange;

	virtual void MakeRange();

	UFUNCTION(BlueprintCallable, Category = "Membership")
	float GetDegreeOfMembership(int32 x);

	UTerm* Copy();

	void Set(
		FName NameOther,
		int32 LowerBoundOther,
		int32 UpperBoundOther
	);

};
