// Fill out your copyright notice in the Description page of Project Settings.


#include "Hedge/HedgeNot.h"

UTerm* UHedgeNot::Compute(UTerm* OriginalSet)
{
    UTerm* NegativeSet = Super::Compute(OriginalSet);
    NegativeSet->Name = "Not" + NegativeSet->Name;

    for (float& value : NegativeSet->ValueRange)
    {
        value = 1 - value;
    }

    return NegativeSet;
}
