// Fill out your copyright notice in the Description page of Project Settings.


#include "Defuzzification/CentroidDefuzzification.h"

int32 UCentroidDefuzzification::Defuzzify(UTerm* Term)
{
    float OutputValue = 0;
    float OverallValue = 0;

    for (int32 Index = Term->LowerBound; Index <= Term->UpperBound; ++Index)
    {
        OutputValue += Term->GetDegreeOfMembership(Index) * Index;
        OverallValue += Term->GetDegreeOfMembership(Index);
    }

    OutputValue /= OverallValue;

    return OutputValue;
}
