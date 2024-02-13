// Fill out your copyright notice in the Description page of Project Settings.


#include "Obstacle.h"
#include "Kismet/KismetMathLibrary.h"
#include "Math/Vector.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
AObstacle::AObstacle()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AObstacle::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AObstacle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AObstacle::CalculateNewEllipseRadius(FRotator rotation, FVector obstacleScale, float &radius) const
{
	float semisideA = DefaultLength * obstacleScale.X;
	float semisideB = DefaultLength * obstacleScale.Y;

	FVector newDirection = rotation.Vector();
	newDirection.Normalize();

	FVector meshDirection = GetActorRotation().Vector();
	meshDirection.Normalize();

	float angle = FVector::DotProduct(meshDirection, newDirection);
	angle = UKismetMathLibrary::Acos(angle);

	float a = FMath::Square(semisideA * UKismetMathLibrary::Cos(angle));
	float b = FMath::Square(semisideB * UKismetMathLibrary::Sin(angle));

	radius = (semisideA * semisideB) / FMath::Sqrt(a + b);
}