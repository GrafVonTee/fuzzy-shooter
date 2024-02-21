// Fill out your copyright notice in the Description page of Project Settings.


#include "FuzzyLib/Variable/Variable.h"
#include "Containers/Map.h"

void UVariable::UpdateDegreeOfMembership(int32 x)
{
	LastValue.Empty();

	for (auto& Elem : Terms)
	{
		LastValue.Add(Elem.Key, Elem.Value->GetDegreeOfMembership(x));
	}

}

void UVariable::AddTerm(FString TermName, UTerm* NewTerm)
{
	NewTerm->MakeRange();
	Terms.Add(TermName, NewTerm);

}

UTerm* UVariable::GetTermFromMapByName(const FString& TargetTermName)
{
	if (!Terms.Contains(TargetTermName)) return nullptr;

	return Terms[TargetTermName];
}

float UVariable::GetValueFromMapByName(const FString& TargetTermName)
{
	if (!LastValue.Contains(TargetTermName)) return 0.0f;

	return LastValue[TargetTermName];
}

void UVariable::ClearTerms()
{
	Terms.Empty();

}

void UVariable::Set(FName NameOther, int32 LowerBoundOther, int32 UpperBoundOther)
{
	Name = NameOther;
	LowerBound = LowerBoundOther;
	UpperBound = UpperBoundOther;
	ClearTerms();
}
