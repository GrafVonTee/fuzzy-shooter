// Fill out your copyright notice in the Description page of Project Settings.


#include "DefaultConsumed.h"

// Sets default values
ADefaultConsumed::ADefaultConsumed()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ADefaultConsumed::BeginPlay()
{
	Super::BeginPlay();

	CurrentValue = FMath::RandRange(50, MaximumValue);
	
}

// Called every frame
void ADefaultConsumed::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

