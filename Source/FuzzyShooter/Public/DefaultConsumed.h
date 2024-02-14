// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InterestPointInterface.h"
#include "DefaultConsumed.generated.h"

UCLASS()
class FUZZYSHOOTER_API ADefaultConsumed : public AActor, public IInterestPointInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADefaultConsumed();

	UPROPERTY(
		EditAnywhere,
		BlueprintReadWrite,
		Category = "Value")
	int32 MaximumValue = 150;

	UPROPERTY(
		EditAnywhere,
		BlueprintReadWrite,
		Category = "Value",
		meta = (ClampMin = 0))
	int32 CurrentValue = 0;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
