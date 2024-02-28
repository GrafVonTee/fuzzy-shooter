// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"

#include "Term/Term.h"
#include "VariableReceiver.h"

#include "Variable.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class FUZZYLIBRARY_API UVariable : public UObject
{
	GENERATED_BODY()
	
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "General")
	FString Name;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Range")
	int32 LowerBound;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Range")
	int32 UpperBound;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "General")
	TMap<FString, UTerm*> Terms;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "General")
	TMap<FString, float> LastValue;

	UPROPERTY()
	UVariableReceiver* Receiver;

	UFUNCTION(BlueprintCallable, Category = "Membership")
	void UpdateDegreeOfMembership(int32 x);

	UFUNCTION(BlueprintCallable, Category = "Membership")
	void AddTerm(FString TermName, UTerm* NewTerm, int32 Weight);

	UFUNCTION(BlueprintCallable, Category = "Membership")
	UTerm* GetTermFromMapByName(const FString& TargetTermName);

	UFUNCTION(BlueprintCallable, Category = "Membership")
	float GetValueFromMapByName(const FString& TargetTermName);

	FString GetTermWithValue(int32 x);

	UFUNCTION(BlueprintCallable, Category = "Membership")
	void ClearTerms();

	void Set(
		FString NameOther,
		int32 LowerBoundOther,
		int32 UpperBoundOther,
		UVariableReceiver* ReceiverOther
	);

	UPROPERTY()
	TMap<FString, int32> WeightsForTerms;

};
