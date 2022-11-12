// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayableCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/DecalComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetNodeHelperLibrary.h"

// Sets default values
APlayableCharacter::APlayableCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Set size for player capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate character to camera direction
	LockRotation();

	ConfigureCharacterMovement();

	// Create a camera boom...
	SetupCameraBoom();

	// Create a camera...
	SetupTopDownCamera();

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

	PopulateSkillArray();
}

// Called every frame
void APlayableCharacter::Tick(const float DeltaTime)
{
	Super::Tick(DeltaTime);

	CalculateLookingDirection();
	CalculateCursorPosition();
}

void APlayableCharacter::LockRotation()
{
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
}

void APlayableCharacter::ConfigureCharacterMovement() const
{
	GetCharacterMovement()->bOrientRotationToMovement = true; // Rotate character to moving direction
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;
}

void APlayableCharacter::SetupCameraBoom()
{
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetUsingAbsoluteRotation(true); // Don't want arm to rotate when character does
	CameraBoom->TargetArmLength = 1000.f;
	CameraBoom->SetRelativeRotation(FRotator(-65.f, 0.f, 0.f));
	CameraBoom->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level
}

void APlayableCharacter::SetupTopDownCamera()
{
	TopDownCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	TopDownCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	TopDownCameraComponent->bUsePawnControlRotation = false; // Camera does not rotate relative to arm
}

void APlayableCharacter::CalculateCursorPosition() const
{
	if (CursorToWorld != nullptr)
	{
		if (const APlayerController* PC = Cast<APlayerController>(GetController()))
		{
			FHitResult TraceHitResult;
			PC->GetHitResultUnderCursor(ECC_Visibility, true, TraceHitResult);
			const FVector CursorFv = TraceHitResult.ImpactNormal;
			const FRotator CursorR = CursorFv.Rotation();
			CursorToWorld->SetWorldLocation(TraceHitResult.Location);
			CursorToWorld->SetWorldRotation(CursorR);
		}
	}
}

FRotator APlayableCharacter::CalculateLookingDirection() const
{
	if (CursorToWorld != nullptr)
	{
		const FVector PlayerPosition = this->GetTransform().GetLocation();
		const FVector CursorPosition = CursorToWorld->GetComponentLocation();
		FRotator ActualRotation = UKismetMathLibrary::FindLookAtRotation(PlayerPosition, CursorPosition);
		ActualRotation.Roll = 0;
		ActualRotation.Pitch = 0;
		GetCapsuleComponent()->SetWorldRotation(ActualRotation);
		return ActualRotation;
	}
	return FRotator::ZeroRotator;
}


void APlayableCharacter::PopulateSkillArray()
{
	for (int i = 0; i < Skills.Num(); ++i)
	{
		if (USkillBase* NewSkill = NewObject<USkillBase>(this, Skills[i]))
		{
			NewSkill->InitializeSkill(this, CachedWorld);
			RuntimeSkills.Add(NewSkill);
		};
	}
}

void APlayableCharacter::UseBasicAttack()
{
	if (RuntimeSkills.IsValidIndex(0))
	{
		FVector v = CursorToWorld->GetComponentLocation();
		FRotator LookRotator = CalculateLookingDirection();
		RuntimeSkills[0]->UseSkill(v, LookRotator);
	}
}

void APlayableCharacter::UseFirstAbility()
{
	if (RuntimeSkills.IsValidIndex(1))
	{
		FVector v = this->GetTransform().GetLocation();
		FRotator LookRotator = FRotator::ZeroRotator;
		RuntimeSkills[1]->UseSkill(v, LookRotator);
	}
}

void APlayableCharacter::UseSecondAbility()
{
	if (RuntimeSkills.IsValidIndex(2))
	{
		FVector v = this->GetTransform().GetLocation();
		FRotator LookRotator = FRotator::ZeroRotator;
		RuntimeSkills[2]->UseSkill(v, LookRotator);
	}
}

void APlayableCharacter::UseThirdAbility()
{
	if (RuntimeSkills.IsValidIndex(3))
	{
		FVector v = this->GetTransform().GetLocation();
		FRotator LookRotator = FRotator::ZeroRotator;
		RuntimeSkills[3]->UseSkill(v, LookRotator);
	}
}
