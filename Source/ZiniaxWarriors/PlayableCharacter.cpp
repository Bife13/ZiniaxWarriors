// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayableCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/DecalComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
APlayableCharacter::APlayableCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Set size for player capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate character to camera direction
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Rotate character to moving direction
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	// Create a camera boom...
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetUsingAbsoluteRotation(true); // Don't want arm to rotate when character does
	CameraBoom->TargetArmLength = 1000.f;
	CameraBoom->SetRelativeRotation(FRotator(-65.f, 0.f, 0.f));
	CameraBoom->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level

	// Create a camera...
	TopDownCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	TopDownCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	TopDownCameraComponent->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Create a decal in the world to show the cursor's location
	CursorToWorld = CreateDefaultSubobject<UDecalComponent>("CursorToWorld");
	CursorToWorld->SetupAttachment(RootComponent);

	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;

}

void APlayableCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (UWorld* World = GetWorld())
	{
		CachedWorld = World;
	}
	for (int i = 0; i < Skills.Num(); ++i)
	{
		if(USkillBase* newSkill = NewObject<USkillBase>(this, Skills[i]))
		{
			newSkill->InitializeSkill(this, CachedWorld);
			RuntimeSkills.Add(newSkill);
		};
	}
}

// Called every frame
void APlayableCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (CursorToWorld != nullptr)
	{
		if (APlayerController* PC = Cast<APlayerController>(GetController()))
		{
			FHitResult TraceHitResult;
			PC->GetHitResultUnderCursor(ECC_Visibility, true, TraceHitResult);
			FVector CursorFV = TraceHitResult.ImpactNormal;
			FRotator CursorR = CursorFV.Rotation();
			CursorToWorld->SetWorldLocation(TraceHitResult.Location);
			CursorToWorld->SetWorldRotation(CursorR);
		}
	}
}

void APlayableCharacter::UseBasicAttack()
{
	if (RuntimeSkills.IsValidIndex(0))
	{
		FVector v = FVector::ZeroVector;
		float ZDirection = 60.0f;
		RuntimeSkills[0]->UseSkill(v, ZDirection);
	}
}

void APlayableCharacter::UseFirstAbility()
{
	if (RuntimeSkills.IsValidIndex(1))
	{
		FVector v = FVector::ZeroVector;
		float ZDirection = 60.0f;
		RuntimeSkills[1]->UseSkill(v, ZDirection);
	}
}

void APlayableCharacter::UseSecondAbility()
{
	if (RuntimeSkills.IsValidIndex(2))
	{
		FVector v = FVector::ZeroVector;
		float ZDirection = 60.0f;
		RuntimeSkills[2]->UseSkill(v, ZDirection);
	}
}

void APlayableCharacter::UseThirdAbility()
{
	if (RuntimeSkills.IsValidIndex(3))
	{
		FVector v = FVector::ZeroVector;
		float ZDirection = 60.0f;
		RuntimeSkills[3]->UseSkill(v, ZDirection);
	}
}
