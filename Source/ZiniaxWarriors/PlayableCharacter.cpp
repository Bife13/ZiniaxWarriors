// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayableCharacter.h"

#include "Buff.h"
#include "DTR_CharacterStats.h"
#include "PowerBuff.h"
#include "Camera/CameraComponent.h"
#include "Components/ArrowComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/DecalComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Particles/ParticleSystem.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
APlayableCharacter::APlayableCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Set size for player capsule
	GetCapsuleComponent()->InitCapsuleSize(60.f, 96.0f);

	// Don't rotate character to camera direction
	LockRotation();

	ConfigureCharacterMovement();

	SetupStatsComponent();
	
	// Create a camera boom...
	SetupCameraBoom();

	// Create a camera...
	SetupTopDownCamera();

	SetupHealthComponent();
	SetupStatusEffectComponent();
	SetupCastParticleSystem();

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


void APlayableCharacter::MoveMouse_Implementation(FVector Value)
{
	const FVector PlayerPosition = this->GetTransform().GetLocation();
	const FVector CursorPosition = Value;
	FRotator ActualRotation = UKismetMathLibrary::FindLookAtRotation(PlayerPosition, CursorPosition);
	ActualRotation.Roll = 0;
	ActualRotation.Pitch = 0;
	CachedMousePosition = CursorPosition;
	CachedMouseRotator = ActualRotation;
	GetCapsuleComponent()->SetWorldRotation(ActualRotation);
}


// Called every frame
void APlayableCharacter::Tick(const float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bIsCasting)
	{
		GetCharacterMovement()->MaxWalkSpeed = BaseSpeed * .3f;
	}
	else
	{
		GetCharacterMovement()->MaxWalkSpeed = BaseSpeed;
	}
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

void APlayableCharacter::SetupStatsComponent()
{
	StatsComponent = CreateDefaultSubobject<UStatsComponent>(TEXT("Stats Component"));
}

void APlayableCharacter::SetupCastParticleSystem()
{
	CastParticleSystem = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Cast Particle"));
	CastParticleSystem->SetupAttachment(RootComponent);
}

void APlayableCharacter::SetupHealthComponent()
{
	HealthComponent = CreateDefaultSubobject<UHealthSystem>(TEXT("Health Component"));
}

void APlayableCharacter::SetupStatusEffectComponent()
{
	StatusEffectsComponent = CreateDefaultSubobject<UStatusEffectsComponent>(TEXT("Status Effect Component"));
}

void APlayableCharacter::SetupStatValues(float PowerValue, float SpeedValue, float MaximumHealthValue,
                                         float ResistanceValue, float ViewRangeValue)
{
	StatsComponent->SetupStatSystem(PowerValue, SpeedValue, MaximumHealthValue, ResistanceValue, ViewRangeValue);
	BaseSpeed = StatsComponent->GetSpeed();
}

void APlayableCharacter::SetupComponentValues()
{
	HealthComponent->SetMaxHealth(StatsComponent->GetMaximumHealth());
	HealthComponent->SetResistance(StatsComponent->GetResistance());
	HealthComponent->SetHealthToMaxHealth();
	StatusEffectsComponent->SetStatsComponent(StatsComponent);
}

void APlayableCharacter::SetupTopDownCamera()
{
	TopDownCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	TopDownCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	TopDownCameraComponent->bUsePawnControlRotation = false; // Camera does not rotate relative to arm
}


void APlayableCharacter::PopulateSkillArray()
{
	for (int i = 0; i < Skills.Num(); ++i)
	{
		if (USkillBase* NewSkill = NewObject<USkillBase>(this, Skills[i]))
		{
			NewSkill->InitializeSkill(this, CachedWorld, TeamID);
			RuntimeSkills.Add(NewSkill);
		};
	}
}

void APlayableCharacter::MoveVertical_Implementation(float Value)
{
	const FVector MoveDirection = {1, 0, 0};
	AddMovementInput(MoveDirection, Value);
}

void APlayableCharacter::MoveHorizontal_Implementation(float Value)
{
	const FVector MoveDirection = {0, 1, 0};
	AddMovementInput(MoveDirection, Value);
}

void APlayableCharacter::UseBasicAttack()
{
	if (RuntimeSkills.IsValidIndex(0))
	{
		RuntimeSkills[0]->CastSkill(AttackAnimations[0]);
	}
}

void APlayableCharacter::UseFirstAbility()
{
	if (RuntimeSkills.IsValidIndex(1))
	{
		RuntimeSkills[1]->CastSkill(AttackAnimations[1]);
	}
}

void APlayableCharacter::UseSecondAbility()
{
	if (RuntimeSkills.IsValidIndex(2))
	{
		RuntimeSkills[2]->CastSkill(AttackAnimations[1]);
	}
}

void APlayableCharacter::UseThirdAbility()
{
	if (RuntimeSkills.IsValidIndex(3))
	{
		RuntimeSkills[3]->CastSkill(AttackAnimations[1]);
	}
}

void APlayableCharacter::TakeDamage(float Amount)
{
	HealthComponent->TakeDamage(Amount);
}

void APlayableCharacter::AddEnrage(float TimeAmount, float BuffAmount)
{
	StatusEffectsComponent->AddPowerBuff(TimeAmount, BuffAmount);
}

void APlayableCharacter::AddBulk(float TimeAmount, float BuffAmount)
{
	StatusEffectsComponent->AddResistanceBuff(TimeAmount, BuffAmount);
}

void APlayableCharacter::AddHaste(float TimeAmount, float BuffAmount)
{
	StatusEffectsComponent->AddSpeedBuff(TimeAmount, BuffAmount);
}

void APlayableCharacter::AddVulnerable(float TimeAmount, float DebuffAmount)
{
	StatusEffectsComponent->AddResistanceDebuff(TimeAmount, DebuffAmount);
}

void APlayableCharacter::AddSlow(float TimeAmount, float DebuffAmount)
{
	StatusEffectsComponent->AddSpeedDebuff(TimeAmount, DebuffAmount);
}

void APlayableCharacter::AddWeaken(float TimeAmount, float DebuffAmount)
{
	StatusEffectsComponent->AddPowerDebuff(TimeAmount, DebuffAmount);
}

void APlayableCharacter::SetCastEffect(UParticleSystem* NewParticle)
{
	CastParticleSystem->Template = NewParticle;
	CastParticleSystem->Activate(true);
}
