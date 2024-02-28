// Fill out your copyright notice in the Description page of Project Settings.


#include "Activation/ProdActivation.h"

UTerm* UProdActivation::GetActivatedSet(float ActivationCoeff, UTerm* OriginalSet)
{
	UTerm* NewSet = Super::GetActivatedSet(ActivationCoeff, OriginalSet);
	NewSet->Name = "Activated";

	for (int32 Index = 0; Index < NewSet->ValueRange.Num(); ++Index)
	{
		NewSet->ValueRange[Index] = ActivationCoeff * NewSet->ValueRange[Index];
	}

	return NewSet;
}
