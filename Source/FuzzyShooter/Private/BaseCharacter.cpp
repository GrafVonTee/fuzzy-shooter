// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCharacter.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
ABaseCharacter::ABaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->MaxWalkSpeed = BaseSpeed;

	GetCapsuleComponent()->InitCapsuleSize(42, 90);
	
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SkelMesh(TEXT("/Game/Mannequin/Character/Mesh/SK_Mannequin.SK_Mannequin"));
	static ConstructorHelpers::FObjectFinder<UAnimSequence> IdleAnim(TEXT("/Game/Mannequin/Animations/ThirdPerson_AnimBP.ThirdPerson_AnimBP"));

	if (SkelMesh.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(SkelMesh.Object);
		GetMesh()->SetRelativeLocation(FVector(0, 0, -85));
		GetMesh()->SetRelativeRotation(FRotator(0, -90, 0));
	}

	if (IdleAnim.Succeeded())
	{
		GetMesh()->SetAnimation(IdleAnim.Object);
	}
	

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
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

void ABaseCharacter::Shoot()
{
	if (CurrentAmmo > 0 && !bIsDead)
	{
		// Reducing ammo
		--CurrentAmmo;

		// Find direction to shoot
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		// here should be code for spawning bullet and shooting
	}
}