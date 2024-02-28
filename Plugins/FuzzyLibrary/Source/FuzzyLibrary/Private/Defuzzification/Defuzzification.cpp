// Fill out your copyright notice in the Description page of Project Settings.


#include "Defuzzification/Defuzzification.h"

int32 UDefuzzification::Defuzzify(UTerm* Term)
{
    return Term->LowerBound;
}
