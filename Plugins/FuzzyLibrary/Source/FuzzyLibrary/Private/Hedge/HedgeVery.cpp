// Fill out your copyright notice in the Description page of Project Settings.


#include "Hedge/HedgeVery.h"

UTerm* UHedgeVery::Compute(UTerm* OriginalSet)
{
	UTerm* VerySet = Super::Compute(OriginalSet);
    VerySet->Name = "Very" + VerySet->Name;

    for (float& value : VerySet->ValueRange)
    {
        value *= value;
    }

    return VerySet;
}
