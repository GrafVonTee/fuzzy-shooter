// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"

#include "FuzzyLib/Term/Term.h"

#include "Variable.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class FUZZYSHOOTER_API UVariable : public UObject
{
	GENERATED_BODY()
	
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "General")
	FName Name;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Range")
	int32 LowerBound;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Range")
	int32 UpperBound;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "General")
	TMap<FString, UTerm*> Terms;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "General")
	TMap<FString, float> LastValue;

	UFUNCTION(BlueprintCallable, Category = "Membership")
	void UpdateDegreeOfMembership(int32 x);

	UFUNCTION(BlueprintCallable, Category = "Membership")
	void AddTerm(FString TermName, UTerm* NewTerm);

	UFUNCTION(BlueprintCallable, Category = "Membership")
	UTerm* GetTermFromMapByName(const FString& TargetTermName);

	UFUNCTION(BlueprintCallable, Category = "Membership")
	float GetValueFromMapByName(const FString& TargetTermName);

	UFUNCTION(BlueprintCallable, Category = "Membership")
	void ClearTerms();

	void Set(
		FName NameOther,
		int32 LowerBound,
		int32 UpperBound
	);
};
