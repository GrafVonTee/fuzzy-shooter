// Fill out your copyright notice in the Description page of Project Settings.


#include "Hedge/HedgeApproximately.h"
#include "Kismet/KismetMathLibrary.h"

UTerm* UHedgeApproximately::Compute(UTerm* OriginalSet)
{
    UTerm* ApproxSet = Super::Compute(OriginalSet);
    ApproxSet->Name = "Approx" + ApproxSet->Name;

    for (float& value : ApproxSet->ValueRange)
    {
        value = UKismetMathLibrary::Sqrt(value);
    }

    return ApproxSet;
}
