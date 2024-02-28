// Fill out your copyright notice in the Description page of Project Settings.


#include "Term/Triangluar.h"

UTriangluar::UTriangluar()
{
}

void UTriangluar::MakeRange()
{
	Super::MakeRange();

	int32 termA, termB, termC;
	termA = PointA - LowerBound;
	termB = PointB - LowerBound;
	termC = PointC - LowerBound;

	for (int32 Index = 0; Index < ValueRange.Num(); ++Index)
	{
		if (Index < termA || Index > termC)
		{
			ValueRange[Index] = 0.0f;
		}
		else if (Index < termB)
		{
			ValueRange[Index] = (Index - termA) * 1.0f / (termB - termA);
		}
		else if (Index == termB)
		{
			ValueRange[Index] = 1;
		}
		else
		{
			ValueRange[Index] = (termC - Index) * 1.0f / (termC - termB);
		}
	}
}

void UTriangluar::Set(
	FString NameOther,
	int32 LowerBoundOther,
	int32 UpperBoundOther,
	int32 PointAOther,
	int32 PointBOther,
	int32 PointCOther
)
{
	Super::Set(NameOther, LowerBoundOther, UpperBoundOther);

	PointA = PointAOther;
	PointB = PointBOther;
	PointC = PointCOther;
	MakeRange();
}
