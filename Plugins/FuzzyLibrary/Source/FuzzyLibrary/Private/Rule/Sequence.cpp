// Fill out your copyright notice in the Description page of Project Settings.


#include "Rule/Sequence.h"
#include "Containers/Map.h"

float USequence::Compute(TMap<UVariable*, int32> Input)
{
	TArray<float> DomInput;

	for (const auto& ElemOfContent : Content)
	{
		UTerm* TempTerm = ElemOfContent.Value;

		DomInput.Add(TempTerm->GetDegreeOfMembership(Input[ElemOfContent.Key]));
	}

	return Aggregation->Compute(DomInput);
}

void USequence::Set(TMap<UVariable*, UTerm*> ContentOther, UAggregation* AggregationOther)
{
	Content = ContentOther;
	Aggregation = AggregationOther;

}
