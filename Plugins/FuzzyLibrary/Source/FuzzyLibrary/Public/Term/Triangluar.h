// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Term.h"
#include "Triangluar.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class FUZZYLIBRARY_API UTriangluar : public UTerm
{
	GENERATED_BODY()

public:
	UTriangluar();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Membership")
	int32 PointA;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Membership")
	int32 PointB;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Membership")
	int32 PointC;

	virtual void MakeRange() override;

	void Set(
		FString NameOther,
		int32 LowerBoundOther,
		int32 UpperBoundOther,
		int32 PointAOther,
		int32 PointBOther,
		int32 PointCOther
	);
};
