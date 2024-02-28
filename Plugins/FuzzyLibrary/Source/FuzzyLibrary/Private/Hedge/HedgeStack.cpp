// Fill out your copyright notice in the Description page of Project Settings.


#include "Hedge/HedgeStack.h"

void UHedgeStack::Clear()
{
	Stack.Empty();
}

void UHedgeStack::Add(UHedge* NewHedge)
{
	Stack.Add(NewHedge);
}

UTerm* UHedgeStack::Compute(UTerm* Term)
{
	UTerm* NewTerm = Term->Copy();

	for (int32 Index = Stack.Num() - 1; Index >= 0; --Index)
	{
		UHedge* TempHedge = Stack[Index];
		NewTerm = TempHedge->Compute(NewTerm);
	}

	return NewTerm;
}
