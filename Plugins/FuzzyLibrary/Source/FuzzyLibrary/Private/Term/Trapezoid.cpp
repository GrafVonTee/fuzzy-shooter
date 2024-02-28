// Fill out your copyright notice in the Description page of Project Settings.


#include "Term/Trapezoid.h"

UTrapezoid::UTrapezoid()
{
}

void UTrapezoid::MakeRange()
{
	Super::MakeRange();

	int32 termA, termB, termC, termD;
	termA = PointA - LowerBound;
	termB = PointB - LowerBound;
	termC = PointC - LowerBound;
	termD = PointD - LowerBound;

	for (int32 Index = 0; Index < ValueRange.Num(); ++Index)
	{
		if (Index < termA || Index > termD)
		{
			ValueRange[Index] = 0.0f;
		}
		else if (Index < termB)
		{
			ValueRange[Index] = (Index - termA) * 1.0f / (termB - termA);
		}
		else if (Index <= termC)
		{
			ValueRange[Index] = 1;
		}
		else
		{
			ValueRange[Index] = (termD - Index) * 1.0f / (termD - termC);
		}
	}
}

void UTrapezoid::Set(
	FString NameOther,
	int32 LowerBoundOther,
	int32 UpperBoundOther,
	int32 PointAOther,
	int32 PointBOther,
	int32 PointCOther,
	int32 PointDOther
)
{
	Super::Set(NameOther, LowerBoundOther, UpperBoundOther);

	PointA = PointAOther;
	PointB = PointBOther;
	PointC = PointCOther;
	PointD = PointDOther;
	MakeRange();
}
