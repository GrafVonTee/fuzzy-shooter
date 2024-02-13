// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCharacter.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Engine/EngineTypes.h"


// Sets default values
ABaseCharacter::ABaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->MaxWalkSpeed = BaseSpeed;

	GetCapsuleComponent()->InitCapsuleSize(42, 90);
	
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SkelMesh(TEXT("/Game/Mannequin/Character/Mesh/SK_Mannequin.SK_Mannequin"));

	if (SkelMesh.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(SkelMesh.Object);
		GetMesh()->SetRelativeLocation(FVector(0, 0, -85));
		GetMesh()->SetRelativeRotation(FRotator(0, -90, 0));
	}

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	SpawnerSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpawnerSpringArm"));
	SpawnerSpringArm->SetupAttachment(RootComponent);
	SpawnerSpringArm->TargetArmLength = 70;
	SpawnerSpringArm->AddLocalRotation(FRotator(0, 180, 0));

	SpawnPoint = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SphereMesh"));
	SpawnPoint->SetupAttachment(SpawnerSpringArm);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> SphereMeshAsset(TEXT("/Engine/BasicShapes/Sphere.Sphere"));
	
	if (SphereMeshAsset.Succeeded())
	{
		SpawnPoint->SetStaticMesh(SphereMeshAsset.Object);
		SpawnPoint->SetRelativeScale3D(FVector(0.2, 0.2, 0.2));
		SpawnPoint->SetVisibility(false);
	}
}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	ResetRegenTimer();

}

// Called every frame
void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

/** Movement Functions */
void ABaseCharacter::MoveForward(float Axis)
{
	if (Controller && !bIsDead && (Axis != 0))
	{
		const FVector Direction(1, 0, 0);
		AddMovementInput(Direction, Axis);
	}
}

void ABaseCharacter::MoveRight(float Axis)
{
	if (Controller && !bIsDead && (Axis != 0))
	{
		const FVector Direction(0, 1, 0);
		AddMovementInput(Direction, Axis);
	}
}

bool ABaseCharacter::CanShoot() const
{
	return (CurrentAmmo > 0) && !bIsDead && !bShootBlocked;
}

void ABaseCharacter::Shoot()
{
	if (CanShoot())
	{
		--CurrentAmmo;
		IAttackInterface::Execute_BeginAttack(this);
		bShootBlocked = true;
	}
}

void ABaseCharacter::StopShooting()
{
	IAttackInterface::Execute_StopAttack(this);
	bShootBlocked = false;
}

void ABaseCharacter::ReceiveDamage(int32 DamageTaken)
{
	ResetRegenTimer();
	CurrentHealth -= DamageTaken;
	if (CurrentHealth <= 0)
	{
		CurrentHealth = 0;
		bIsDead = true;
		OnDestroyAction();
	}

}

void ABaseCharacter::RegenHealth()
{
	CurrentHealth += RegenValue;
	CurrentHealth = FMath::Clamp(CurrentHealth, 0, MaxHealth);

}

void ABaseCharacter::ResetRegenTimer()
{
	GetWorldTimerManager().SetTimer(RegenTimerHandle, this, &ABaseCharacter::RegenHealth, RegenRate, true);

}