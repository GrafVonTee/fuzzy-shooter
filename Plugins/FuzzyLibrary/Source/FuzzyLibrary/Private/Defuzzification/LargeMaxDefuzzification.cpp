// Fill out your copyright notice in the Description page of Project Settings.


#include "Defuzzification/LargeMaxDefuzzification.h"

int32 ULargeMaxDefuzzification::Defuzzify(UTerm* Term)
{
    int32 MaxIndex = Term->LowerBound;
    float MaxValue = Term->GetDegreeOfMembership(MaxIndex);

    for (int32 Index = Term->LowerBound; Index <= Term->UpperBound; ++Index)
    {
        if (MaxValue <= Term->GetDegreeOfMembership(Index))
        {
            MaxIndex = Index;
            MaxValue = Term->GetDegreeOfMembership(Index);
        }
    }

    return MaxIndex;
}