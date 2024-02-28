// Fill out your copyright notice in the Description page of Project Settings.


#include "Accumulation/MaxAccumulation.h"

UTerm* UMaxAccumulation::Compute(TArray<UTerm*> TermList)
{
	if (TermList.Num() == 0)
	{
		return nullptr;
	}

	UTerm* MaxTerm = TermList[0]->Copy();
	MaxTerm->Name = "Accumulated";

	for (int32 Index = MaxTerm->LowerBound; Index <= MaxTerm->UpperBound; ++Index)
	{
		for (UTerm* Term : TermList)
		{
			if (MaxTerm->ValueRange[Index] < Term->ValueRange[Index])
			{
				MaxTerm->ValueRange[Index] = Term->ValueRange[Index];
			}
		}
	}

	return MaxTerm;
}
