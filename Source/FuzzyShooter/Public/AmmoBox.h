// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AmmoBox.generated.h"

const int32 MAXIMUM_VALUE_OF_AMMO = 150;

UCLASS()
class FUZZYSHOOTER_API AAmmoBox : public AActor
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	AAmmoBox();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Variables")
	int32 AmmoValue2 = 0;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
