// Fill out your copyright notice in the Description page of Project Settings.


#include "Variable/Variable.h"
#include "Containers/Map.h"

void UVariable::UpdateDegreeOfMembership(int32 x)
{
	LastValue.Empty();

	for (auto& Elem : Terms)
	{
		LastValue.Add(Elem.Key, Elem.Value->GetDegreeOfMembership(x));
	}

}

void UVariable::AddTerm(FString TermName, UTerm* NewTerm, int32 Weight)
{
	NewTerm->MakeRange();
	Terms.Add(TermName, NewTerm);
	WeightsForTerms.Add(TermName, Weight);
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

FString UVariable::GetTermWithValue(int32 x)
{
	UpdateDegreeOfMembership(x);
	auto WeightedValue = LastValue;
	for (auto& Elem : WeightedValue)
	{
		WeightedValue[Elem.Key] *= WeightsForTerms[Elem.Key];
	}
	return Receiver->Receive(LastValue);

}

void UVariable::ClearTerms()
{
	Terms.Empty();

}

void UVariable::Set(
	FString NameOther,
	int32 LowerBoundOther,
	int32 UpperBoundOther,
	UVariableReceiver* ReceiverOther
)
{
	Name = NameOther;
	LowerBound = LowerBoundOther;
	UpperBound = UpperBoundOther;
	Receiver = ReceiverOther;
	ClearTerms();
}
