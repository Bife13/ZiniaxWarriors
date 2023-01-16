// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayableCharacter.h"

#include "Buff.h"
#include "ModuleDescriptor.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Engine/ActorChannel.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Net/UnrealNetwork.h"
#include "Particles/ParticleSystem.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
APlayableCharacter::APlayableCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Set size for player capsule
	GetCapsuleComponent()->InitCapsuleSize(45.f, 96.0f);

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
	SetupRootParticleSystem();
	SetupShieldParticleSystem();
	SetupEnrageParticleSystem();
	SetupVulnerableParticleSystem();
	SetupHasteParticleSystem();
	SetupWeakenParticleSystem();
	SetupSlowParticleSystem();


	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
}

void APlayableCharacter::StartBeginPlay()
{
	if (UWorld* World = GetWorld())
	{
		CachedWorld = World;
	}

	OnCatchphraseSound();

	PopulateSkillArray();
	PassiveInitializeFunction();

	//Haste observe
	StatsComponent->OnHasteAppliedEvent.AddUFunction(this, "ObserveSpeedBuffs");
	StatsComponent->OnHasteRemovedEvent.AddUFunction(this, "ObserveSpeedBuffs");
	StatsComponent->OnHasteAppliedEvent.AddUFunction(this, "StartHasteEffect");
	StatsComponent->OnHasteRemovedEvent.AddUFunction(this, "EndHasteEffect");
	//Slow observe
	StatsComponent->OnSlowAppliedEvent.AddUFunction(this, "ObserveSpeedBuffs");
	StatsComponent->OnSlowRemovedEvent.AddUFunction(this, "ObserveSpeedBuffs");
	StatsComponent->OnSlowAppliedEvent.AddUFunction(this, "StartSlowEffect");
	StatsComponent->OnSlowRemovedEvent.AddUFunction(this, "EndSlowEffect");
	//Casting Slow Observe
	StatsComponent->OnCastingSlowApplied.AddUFunction(this, "ObserveSpeedBuffs");
	StatsComponent->OnCastingSlowRemovedEvent.AddUFunction(this, "ObserveSpeedBuffs");
	//Root observe
	StatsComponent->OnRootApplied.AddUFunction(this, "ObserveSpeedBuffs");
	StatsComponent->OnRootApplied.AddUFunction(this, "StartRootEffect");
	StatsComponent->OnRootRemoved.AddUFunction(this, "ObserveSpeedBuffs");
	StatsComponent->OnRootRemoved.AddUFunction(this, "EndRootEffect");
	//Vulnerable observe
	StatsComponent->OnVulnerableAppliedEvent.AddUFunction(this, "ObserverResistanceBuffs");
	StatsComponent->OnVulnerableRemovedEvent.AddUFunction(this, "ObserverResistanceBuffs");
	StatsComponent->OnVulnerableAppliedEvent.AddUFunction(this, "StartVulnerableEffect");
	StatsComponent->OnVulnerableRemovedEvent.AddUFunction(this, "EndVulnerableEffect");
	//Shield observe
	StatsComponent->OnShieldApplied.AddUFunction(this, "ObserverShieldBuffs");
	StatsComponent->OnShieldRemoved.AddUFunction(this, "ObserverShieldBuffs");
	StatsComponent->OnShieldApplied.AddUFunction(this, "Shielded");
	StatsComponent->OnShieldRemoved.AddUFunction(this, "ShieldOver");
	HealthComponent->OnShieldBrokenEvent.AddUFunction(this, "ShieldOver");
	//Enrage observe
	StatsComponent->OnEnrageAppliedEvent.AddUFunction(this, "StartEnrageEffect");
	StatsComponent->OnEnrageRemovedEvent.AddUFunction(this, "EndEnrageEffect");
	//Weaken Observe
	StatsComponent->OnWeakenAppliedEvent.AddUFunction(this, "StartWeakenEffect");
	StatsComponent->OnWeakenRemovedEvent.AddUFunction(this, "EndWeakenEffect");

	HealthComponent->OnDeathEvent.AddUFunction(this,"CallBPDeathEvent");
	HealthComponent->OnGotHitEvent.AddUFunction(this,"CallBPGotHitEvent");
	HealthComponent->OnLowHealth.AddUFunction(this,"CallBPLowHealthEvent");
	HealthComponent->OnHealedEvent.AddUFunction(this,"CallBPHealedEvent");
}

bool APlayableCharacter::ReplicateSubobjects(UActorChannel* Channel, FOutBunch* Bunch, FReplicationFlags* RepFlags)
{
	bool Wrote = Super::ReplicateSubobjects(Channel, Bunch, RepFlags);

	for (int i = 0; i < RuntimeSkills.Num(); ++i)
	{
		Wrote |= Channel->ReplicateSubobject(RuntimeSkills[i], *Bunch, *RepFlags);
	}
	return Wrote;
}

void APlayableCharacter::SetSkills(TSubclassOf<USkillBase> Ability1, TSubclassOf<USkillBase> Ability2,
                                   TSubclassOf<USkillBase> Ability3)
{
	Skills[1] = Ability1;
	Skills[2] = Ability2;
	Skills[3] = Ability3;
}

void APlayableCharacter::SetServerTeamId_Implementation(float Value)
{
	ServerTeamID = Value;
}

void APlayableCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(APlayableCharacter, CachedMousePosition);
	DOREPLIFETIME(APlayableCharacter, ServerTeamID);
	DOREPLIFETIME(APlayableCharacter, bIsCasting);
	DOREPLIFETIME(APlayableCharacter, bIsDead);
	DOREPLIFETIME(APlayableCharacter, AttackAnimations);
	DOREPLIFETIME(APlayableCharacter, RuntimeSkills);
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
	this->SetActorRotation(FMath::Lerp(GetActorRotation(), ActualRotation, 0.6f));
}

FVector APlayableCharacter::GetMousePos()
{
	return CachedMousePosition;
}


// Called every frame
void APlayableCharacter::Tick(const float DeltaTime)
{
	Super::Tick(DeltaTime);

	OnTickPassive(DeltaTime);


	GetCharacterMovement()->MaxWalkSpeed = BaseSpeed;
}



void APlayableCharacter::LockRotation()
{
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
}

void APlayableCharacter::ConfigureCharacterMovement() const
{
	GetCharacterMovement()->bOrientRotationToMovement = false; // Rotate character to moving direction
	GetCharacterMovement()->RotationRate = FRotator(0.f, 0.f, 0.f);
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

void APlayableCharacter::SetupRootParticleSystem()
{
	RootParticleSystem = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Root Particle"));
	RootParticleSystem->SetupAttachment(RootComponent);
}

void APlayableCharacter::SetupShieldParticleSystem()
{
	ShieldParticleSystem = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Shield Particle"));
	ShieldParticleSystem->SetupAttachment(RootComponent);

	ShieldParticleSystemOver = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Shield Particle Over"));
	ShieldParticleSystemOver->SetupAttachment(RootComponent);
}

void APlayableCharacter::SetupEnrageParticleSystem()
{
	EnrageParticleSystem = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Enrage Particle System"));
	EnrageParticleSystem->SetupAttachment(RootComponent);
}

void APlayableCharacter::SetupVulnerableParticleSystem()
{
	VulnerableParticleSystem = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Vulnerable Particle System"));
	VulnerableParticleSystem->SetupAttachment(RootComponent);
}

void APlayableCharacter::SetupHasteParticleSystem()
{
	HasteParticleSystem = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("HASTE Particle System"));
	HasteParticleSystem->SetupAttachment(RootComponent);
}

void APlayableCharacter::SetupSlowParticleSystem()
{
	SlowParticleSystem = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("SLOW Particle System"));
	SlowParticleSystem->SetupAttachment(RootComponent);
}

void APlayableCharacter::SetupWeakenParticleSystem()
{
	WeakenParticleSystem = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Weaken Particle System"));
	WeakenParticleSystem->SetupAttachment(RootComponent);
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


void APlayableCharacter::PopulateSkillArray_Implementation()
{
	for (int i = 0; i < Skills.Num(); ++i)
	{
		if (USkillBase* NewSkill = NewObject<USkillBase>(this, Skills[i]))
		{
			NewSkill->InitializeSkill(this, CachedWorld, ServerTeamID);
			RuntimeSkills.Add(NewSkill);
		};
	}
}

void APlayableCharacter::ObserveSpeedBuffs()
{
	BaseSpeed = StatsComponent->GetSpeed();
}

void APlayableCharacter::ObserverResistanceBuffs()
{
	HealthComponent->SetResistance(StatsComponent->GetResistance());
}

void APlayableCharacter::ObserverShieldBuffs()
{
	HealthComponent->SetShield(StatsComponent->GetShield());
}


void APlayableCharacter::MoveVertical_Implementation(float Value)
{
	GEngine->AddOnScreenDebugMessage(1, 2, FColor::Red, "Vertical");
	const FVector MoveDirection = {1, 0, 0};
	AddMovementInput(MoveDirection, Value);
	OnFootstepsSound();

}

void APlayableCharacter::MoveHorizontal_Implementation(float Value)
{
	GEngine->AddOnScreenDebugMessage(1, 2, FColor::Red, "Horizontal");
	const FVector MoveDirection = {0, 1, 0};
	AddMovementInput(MoveDirection, Value);
	OnFootstepsSound();
}


void APlayableCharacter::HandleCastEvent1_Implementation(float Value)
{
	CastEventBasic.Broadcast(Value);
}

void APlayableCharacter::HandleCastEvent2_Implementation(float Value)
{
	CastEventAbility1.Broadcast(Value);

}
void APlayableCharacter::HandleCastEvent3_Implementation(float Value)
{
	CastEventAbility2.Broadcast(Value);

}
void APlayableCharacter::HandleCastEvent4_Implementation(float Value)
{
	CastEventAbility3.Broadcast(Value);

}

void APlayableCharacter::UseBasicAttack_Implementation()
{
	if (RuntimeSkills.IsValidIndex(0) && !GetIsCasting() && RuntimeSkills[0]->bCanUse)
	{
		RuntimeSkills[0]->CastSkill(AttackAnimations[0]);
		HandleCastEvent1(RuntimeSkills[0]->AbilityCooldown);
	}
}

void APlayableCharacter::UseFirstAbility_Implementation()
{
	if (RuntimeSkills.IsValidIndex(1) && !GetIsCasting()&& RuntimeSkills[1]->bCanUse)
	{
		RuntimeSkills[1]->CastSkill(AttackAnimations[1]);
		HandleCastEvent2(RuntimeSkills[1]->AbilityCooldown);
		OnHandleAbilitySound();
	}
	else
	{
		OnAbilityOnCooldownSound();
	}
}

void APlayableCharacter::UseSecondAbility_Implementation()
{
	if (RuntimeSkills.IsValidIndex(2) && !GetIsCasting()&& RuntimeSkills[2]->bCanUse)
	{
		RuntimeSkills[2]->CastSkill(AttackAnimations[2]);
		HandleCastEvent3(RuntimeSkills[2]->AbilityCooldown);
		OnHandleAbilitySound();
	}else
	{
		OnAbilityOnCooldownSound();
	}
}

void APlayableCharacter::UseThirdAbility_Implementation()
{
	if (RuntimeSkills.IsValidIndex(3) && !GetIsCasting() && RuntimeSkills[3]->bCanUse)
	{
		RuntimeSkills[3]->CastSkill(AttackAnimations[3]);
		HandleCastEvent4(RuntimeSkills[3]->AbilityCooldown);
		OnHandleAbilitySound();
	}else
	{
		OnAbilityOnCooldownSound();
	}
}

void APlayableCharacter::PassiveInitializeFunction_Implementation()
{
	if (Passive)
	{
		UPassiveBase* NewPassive = NewObject<UPassiveBase>(this, Passive);
		NewPassive->InitializePassive(this);
		RunTimePassive = NewPassive;
		CachedPassiveInterface = Cast<IPassive>(NewPassive);
	}
}

void APlayableCharacter::OnHit()
{
	if (HasAuthority())
		if (CachedPassiveInterface && RunTimePassive)
		{
			CachedPassiveInterface->OnHit();
			OnHitSound();
		}
}

float APlayableCharacter::CheckDistance(float Damage, APawn* OwnerPassive, APawn* Target)
{
	if (HasAuthority())
	{
		if (CachedPassiveInterface && RunTimePassive)
			return CachedPassiveInterface->CheckDistance(Damage, OwnerPassive, Target);
	}
	return 0;
}

void APlayableCharacter::OnTickPassive(float DeltaTime) const
{
	if (HasAuthority())
		if (CachedPassiveInterface)
			CachedPassiveInterface->OnTick(DeltaTime);
}

void APlayableCharacter::OnSpecialAbility(int Index)
{
	OnSpecialAbilityCast(Index);
}



void APlayableCharacter::TakeDamage(float Amount)
{
	HealthComponent->TakeDamage(Amount);
}

void APlayableCharacter::RecoverHealth(float Amount)
{
	HealthComponent->RecoverHealth(Amount);
}

void APlayableCharacter::AddEnrage(float TimeAmount, float BuffAmount)
{
	StatusEffectsComponent->AddEnrage(TimeAmount, BuffAmount);
}

void APlayableCharacter::AddBulk(float TimeAmount, float BuffAmount)
{
	StatusEffectsComponent->AddBulk(TimeAmount, BuffAmount);
}

void APlayableCharacter::AddHaste(float TimeAmount, float BuffAmount)
{
	StatusEffectsComponent->AddHaste(TimeAmount, BuffAmount);
}

void APlayableCharacter::AddHastePassive_Implementation(float TimeAmount, float BuffAmount)
{
	StatusEffectsComponent->AddHaste(TimeAmount, BuffAmount);
}

void APlayableCharacter::AddVulnerable(float TimeAmount, float DebuffAmount)
{
	StatusEffectsComponent->AddVulnerable(TimeAmount, DebuffAmount);
}

void APlayableCharacter::AddVulnerableMulticast_Implementation(float TimeAmount, float DebuffAmount)
{
	StatusEffectsComponent->AddVulnerable(TimeAmount, DebuffAmount);
}

void APlayableCharacter::AddSlow(float TimeAmount, float DebuffAmount)
{
	StatusEffectsComponent->AddSlow(TimeAmount, DebuffAmount);
}

void APlayableCharacter::AddSlowMulticast_Implementation(float TimeAmount, float DebuffAmount)
{
	StatusEffectsComponent->AddSlow(TimeAmount, DebuffAmount);
}

void APlayableCharacter::AddWeaken(float TimeAmount, float DebuffAmount)
{
	StatusEffectsComponent->AddWeaken(TimeAmount, DebuffAmount);
}

void APlayableCharacter::AddWeakenMulticast_Implementation(float TimeAmount, float DebuffAmount)
{
	StatusEffectsComponent->AddWeaken(TimeAmount, DebuffAmount);
}

void APlayableCharacter::AddRoot(float TimeAmount)
{
	StatusEffectsComponent->AddRoot(TimeAmount);
}

void APlayableCharacter::AddShield(float TimeAmount, float BuffAmount)
{
	StatusEffectsComponent->AddShield(TimeAmount, BuffAmount);
}

void APlayableCharacter::AddShieldPassive_Implementation(float TimeAmount, float BuffAmount)
{
	StatusEffectsComponent->AddShield(TimeAmount, BuffAmount);
}

void APlayableCharacter::AddCastingSlow_Implementation(float TimeAmount, float BuffAmount)
{
	StatusEffectsComponent->AddCastingSlow(TimeAmount, BuffAmount);
}

void APlayableCharacter::SetCastEffect(UParticleSystem* NewParticle)
{
	// CastParticleSystem->ForceReset();
	//  if (CastParticleSystem)
	// {
	// 	CastParticleSystem->Template = NewParticle;
	// 	CastParticleSystem->Activate(true);
	//  }
}

void APlayableCharacter::StartRootEffect_Implementation() const
{
	if (RootParticleSystem)
		RootParticleSystem->Activate(true);
}

void APlayableCharacter::EndRootEffect_Implementation() const
{
	if (RootParticleSystem)
	{
		RootParticleSystem->Deactivate();
	}
}

void APlayableCharacter::Shielded_Implementation() const
{
	if (ShieldParticleSystem)
	{
		ShieldParticleSystem->Activate(true);
	}
}

void APlayableCharacter::ShieldOver_Implementation() const
{
	if (ShieldParticleSystemOver && ShieldParticleSystem)
	{
		ShieldParticleSystem->Deactivate();

		ShieldParticleSystemOver->Activate(true);
	}
}

void APlayableCharacter::StartEnrageEffect_Implementation() const
{
	EnrageParticleSystem->Activate(true);
}

void APlayableCharacter::EndEnrageEffect_Implementation() const
{
	EnrageParticleSystem->Deactivate();
}

void APlayableCharacter::StartVulnerableEffect_Implementation() const
{
	VulnerableParticleSystem->Activate(true);
}

void APlayableCharacter::EndVulnerableEffect_Implementation() const
{
	VulnerableParticleSystem->Deactivate();
}

void APlayableCharacter::StartHasteEffect_Implementation() const
{
	HasteParticleSystem->Activate(true);
}

void APlayableCharacter::EndHasteEffect_Implementation() const
{
	HasteParticleSystem->Deactivate();
}

void APlayableCharacter::StartSlowEffect_Implementation() const
{
	SlowParticleSystem->Activate(true);
}

void APlayableCharacter::EndSlowEffect_Implementation() const
{
	SlowParticleSystem->Deactivate();
}

void APlayableCharacter::StartWeakenEffect_Implementation() const
{
	WeakenParticleSystem->Activate(true);
}

void APlayableCharacter::EndWeakenEffect_Implementation() const
{
	WeakenParticleSystem->Deactivate();
}


void APlayableCharacter::CallBPDeathEvent()
{
	OnDeathSound();
}

void APlayableCharacter::CallBPGotHitEvent()
{
	OnGotHitSound();
}

void APlayableCharacter::CallBPLowHealthEvent()
{
	OnLowHealthSound();
}

void APlayableCharacter::CallBPHealedEvent()
{
	OnHealedSound();
}

bool APlayableCharacter::GetIsCasting()
{
	return bIsCasting;
}

void APlayableCharacter::SetIsCasting_Implementation(bool Value)
{
	bIsCasting = Value;
}

bool APlayableCharacter::GetIsDead()
{
	return bIsCasting;
}

void APlayableCharacter::SetIsDead_Implementation(bool Value)
{
	bIsCasting = Value;
}


TArray<USkillBase*> APlayableCharacter::GetRunTimeSkill()
{
	TArray<USkillBase*> SkillsToSend = RuntimeSkills;
	return SkillsToSend;
}

void APlayableCharacter::ResetCharacter()
{
	HealthComponent->SetHealthToMaxHealth();
	StatusEffectsComponent->CleanBuffs();
	OnCatchphraseSound();
}

