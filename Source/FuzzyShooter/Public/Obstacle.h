// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InterestPointInterface.h"
#include "Obstacle.generated.h"

UCLASS()
class FUZZYSHOOTER_API AObstacle : public AActor, public IInterestPointInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AObstacle();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Length")
	float DefaultLength = 80;

	UFUNCTION(BlueprintCallable, Category = "Calculating")
	void CalculateNewEllipseRadius(FRotator rotation, FVector obstacleScale, float &radius) const;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
