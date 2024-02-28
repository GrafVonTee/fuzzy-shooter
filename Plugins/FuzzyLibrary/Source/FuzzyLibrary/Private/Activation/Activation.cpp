// Fill out your copyright notice in the Description page of Project Settings.


#include "Activation/Activation.h"

UTerm* UActivation::GetActivatedSet(float ActivationCoeff, UTerm* OriginalSet)
{
	return OriginalSet->Copy();
}
