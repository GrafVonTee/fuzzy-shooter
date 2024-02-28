// Fill out your copyright notice in the Description page of Project Settings.


#include "Term/Term.h"
#include "Containers/UnrealString.h"
#include "Containers/Array.h"

void UTerm::MakeRange()
{
	ValueRange.Empty();
	ValueRange.Init(0.0f, UpperBound - LowerBound + 1);
}

float UTerm::GetDegreeOfMembership(int32 x)
{
	if (x > UpperBound || x < LowerBound)
	{
		return 0.0f;
	}

	return ValueRange[x - LowerBound];
}

UTerm* UTerm::Copy()
{
	UTerm* CopyTerm = NewObject<UTerm>();
	CopyTerm->Name = Name;
	CopyTerm->LowerBound = LowerBound;
	CopyTerm->UpperBound = UpperBound;
	
	const auto TempValueRange = ValueRange;
	CopyTerm->ValueRange = TempValueRange;

	return CopyTerm;
}

void UTerm::Set(
	FString NameOther,
	int32 LowerBoundOther,
	int32 UpperBoundOther
)
{
	Name = NameOther;
	LowerBound = LowerBoundOther;
	UpperBound = UpperBoundOther;
	MakeRange();

}
