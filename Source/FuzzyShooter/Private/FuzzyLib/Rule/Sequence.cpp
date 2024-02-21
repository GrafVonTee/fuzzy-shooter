// Fill out your copyright notice in the Description page of Project Settings.


#include "FuzzyLib/Rule/Sequence.h"
#include "Containers/Map.h"

float USequence::Compute(TMap<UVariable*, int32> Input)
{
	TArray<float> DomInput;

	for (auto& ElemOfContent : Content)
	{
		UTerm* TempTerm = ElemOfContent.Key->GetTermFromMapByName(ElemOfContent.Value);

		DomInput.Add(TempTerm->GetDegreeOfMembership(Input[ElemOfContent.Key]));
	}

	return Aggregation->Compute(DomInput);
}

void USequence::Set(TMap<UVariable*, FString> ContentOther, UAggregation* AggregationOther)
{
	Content = ContentOther;
	Aggregation = AggregationOther;

}
