// Fill out your copyright notice in the Description page of Project Settings.


#include "Rule/RuleParser.h"
#include "Hedge/HedgeStack.h"

enum ParsedWordType
{
	Variable,
	Hedge,
	Term,
	All
};

void URuleParser::Set(
	TMap<FString, UVariable*> VarList,
	TMap<FString, UHedge*> HedgeList,
	UAggregation* AggregationOther,
	UActivation* ActivationOther
)
{
	VarMap = VarList;
	HedgeMap = HedgeList;
	Aggregation = AggregationOther;
	Activation = ActivationOther;
}

URule* URuleParser::ParseRule(FString Input)
{
	TArray<FString> DelimitedString;
	const TCHAR* Delimeter = TEXT(" ");
	Input.ParseIntoArray(DelimitedString, Delimeter);

	URule* Rule = NewObject<URule>();
	USequence* Antecedent = NewObject<USequence>();

	TMap<UVariable*, UTerm*> RuleCondition;
	UVariable* TempVariable = NewObject<UVariable>(); // just for compilation
	UHedgeStack* HedgeStack = NewObject<UHedgeStack>();
	HedgeStack->Add(HedgeMap[""]);
	FString TempTermName;

	ParsedWordType ParsingOperation = ParsedWordType::All;

	for (const FString& Word : DelimitedString)
	{
		if (Word.Equals("IF"))
		{
			ParsingOperation = ParsedWordType::Variable;
		}
		else if (Word.Equals("IS"))
		{
			ParsingOperation = ParsedWordType::Hedge;
		}
		else if (Word.Equals("THEN") || Word.Equals("AND"))
		{
			RuleCondition.Add(TempVariable, HedgeStack->Compute(TempVariable->GetTermFromMapByName(TempTermName)));
			HedgeStack->Clear();

			ParsingOperation = ParsedWordType::Variable;
		}
		else
		{
			switch (ParsingOperation)
			{
				case ParsedWordType::Variable:
					if (!VarMap.Contains(Word))
					{
						return nullptr;
					}
					TempVariable = VarMap[Word];
					break;

				case ParsedWordType::Hedge:
					if (HedgeMap.Contains(Word))
					{
						HedgeStack->Add(HedgeMap[Word]);
						break;
					}
					HedgeStack->Add(HedgeMap[""]);

				case ParsedWordType::Term:
					if (!TempVariable->GetTermFromMapByName(Word))
					{
						return nullptr;
					}
					TempTermName = Word;
					break;

				default:
					break;

			}
		}
	}

	UTerm* Consequent = TempVariable->GetTermFromMapByName(TempTermName);

	Antecedent->Set(RuleCondition, Aggregation);
	Rule->Set(Antecedent, Consequent, Activation);

	return Rule;

}
