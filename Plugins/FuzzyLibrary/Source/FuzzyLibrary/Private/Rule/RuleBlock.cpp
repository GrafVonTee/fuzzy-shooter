// Fill out your copyright notice in the Description page of Project Settings.


#include "Rule/RuleBlock.h"

void URuleBlock::AddRuleToList(URule* Rule)
{
	RuleList.Add(Rule);

}

void URuleBlock::SetAccumulation(UAccumulation* AccumulationOther)
{
	Accumulation = AccumulationOther;

}

UTerm* URuleBlock::Accumulate(TMap<UVariable*, int32> Input)
{
	TArray<UTerm*> TermList;
	for (auto& Rule : RuleList)
	{
		TermList.Add(Rule->Activate(Input));
	}

	return Accumulation->Compute(TermList);
}
