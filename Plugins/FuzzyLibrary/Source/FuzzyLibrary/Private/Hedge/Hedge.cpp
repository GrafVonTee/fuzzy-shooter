// Fill out your copyright notice in the Description page of Project Settings.


#include "Hedge/Hedge.h"

UTerm* UHedge::Compute(UTerm* OriginalSet)
{
    return OriginalSet->Copy();
}
