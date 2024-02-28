// Fill out your copyright notice in the Description page of Project Settings.


#include "Variable/MaxReceiver.h"

FString UMaxReceiver::Receive(TMap<FString, float> List)
{
	FString MaxName = TEXT("");
	float MaxValue = 0;

	for (auto& Elem : List)
	{
		if (Elem.Value >= MaxValue)
		{
			MaxName = Elem.Key;
			MaxValue = Elem.Value;
		}
	}

	return MaxName;

}
