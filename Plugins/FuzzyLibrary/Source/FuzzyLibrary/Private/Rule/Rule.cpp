// Fill out your copyright notice in the Description page of Project Settings.


#include "Rule/Rule.h"

UTerm* URule::Activate(TMap<UVariable*, int32> Input)
{
	float ActivationCoeff = Antecedent->Compute(Input);

	return Activation->GetActivatedSet(ActivationCoeff, Consequent);

}

void URule::Set(USequence* AntecedentOther, UTerm* ConsequentOther, UActivation* ActivationOther)
{
	Antecedent = AntecedentOther;
	Consequent = ConsequentOther->Copy();
	Activation = ActivationOther;

}
