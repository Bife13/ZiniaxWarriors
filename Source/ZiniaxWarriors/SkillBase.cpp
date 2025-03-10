// Fill out your copyright notice in the Description page of Project Settings.


#include "SkillBase.h"
#include "PlayableCharacter.h"
#include "SkillActor.h"
#include "Components/DecalComponent.h"
#include "Net/UnrealNetwork.h"

void USkillBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(USkillBase, SkillIconTexture);
}

void USkillBase::InitializeSkill(ACharacter* Playable, UWorld* World, int Team)
{
	OwnerCharacter = Playable;
	CachedWorld = World;
	TeamId = Team;
	CachedCharacterInterface = Cast<IUsableCharacterSkillSlot>(OwnerCharacter);
	bCanUse = true;
	OnInitialize();
}


void USkillBase::CastSkill(UAnimMontage* AnimationToPlay)
{
	if (bCanUse)
	{
		CachedCharacterInterface->SetIsCasting(true);
		AttackAnimation = AnimationToPlay;
		bCanUse = false;
		HandleCastEvents(AbilityCooldown);
		OnCast();
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(1, 2, FColor::Red, "On Cooldown");
	}
}

bool USkillBase::IsSupportedForNetworking() const
{
	return true;
}

void USkillBase::HandleCastEvents_Implementation(float Value)
{
	// CastEvent.Broadcast(Value);
}


void USkillBase::HandleResetEvents_Implementation()
{
	ResetEvent.Broadcast(true);
}

// void USkillBase::StartCooldownTimer()
// {
// 	FTimerHandle THandle;
// 	const float Delay = AbilityCooldown;
// 	CachedWorld->GetTimerManager().SetTimer(THandle, this, &USkillBase::ResetCooldown, Delay, false);
// }
//
void USkillBase::DelayedSpawnTimer(const FVector& SpawnPosition, float NumberOfProjectile)
{
	FTimerHandle THandle;
	const float Delay = AbilitySpawnTime * NumberOfProjectile;
	FTimerDelegate DelaySpawnDelegate;
	DelaySpawnDelegate.BindUFunction(this, FName("DelayedSpawn"), OwnerCharacter->GetActorLocation());
	CachedWorld->GetTimerManager().SetTimer(THandle, DelaySpawnDelegate, Delay, false);
}

void USkillBase::DelayedSpawn(const FVector& SpawnPosition)
{
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	AActor* SpawnedAbility = CachedWorld->SpawnActor(ActorToSpawn, &SpawnPosition, &AbilityRotation, SpawnParams);
	const ISkillActor* SkillActorInterface = Cast<ISkillActor>(SpawnedAbility);
	SkillActorInterface->Execute_SetValues(SpawnedAbility, TeamId, AbilityDamage, AbilityRange, SpawnPosition,
	                                       OwnerCharacter);
}

void USkillBase::ResetCooldown_Implementation()
{
	bCanUse = true;
	HandleResetEvents();
}

void USkillBase::UseSkill()
{
	const APlayableCharacter* PlayableCharacter = Cast<APlayableCharacter>(OwnerCharacter);
	AbilityRotation = PlayableCharacter->CachedMouseRotator;
	CachedCharacterInterface->SetIsCasting(false);
	OnUse();
}

void USkillBase::SetCooldown(const float Cooldown)
{
	AbilityCooldown = Cooldown;
}

void USkillBase::SetCastTime(const float CastTime)
{
	AbilityCastTime = CastTime;
}

void USkillBase::SetSpawnTime(float SpawnTime)
{
	AbilitySpawnTime = SpawnTime;
}

void USkillBase::SetAbilityDamage(const float Power, float AbilityPower, float AddValue)
{
	AbilityDamage = (Power * AbilityPower) + AddValue;
}

void USkillBase::SetAbilityRange(const float Range)
{
	AbilityRange = Range;
}


void USkillBase::SpawnSkillActor(const FVector& SpawnPosition)
{
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	AActor* SpawnedAbility = CachedWorld->SpawnActor(ActorToSpawn, &SpawnPosition, &AbilityRotation, SpawnParams);
	const ISkillActor* SkillActorInterface = Cast<ISkillActor>(SpawnedAbility);
	SkillActorInterface->Execute_SetValues(SpawnedAbility, TeamId, AbilityDamage, AbilityRange, SpawnPosition,
	                                       OwnerCharacter);
}


void USkillBase::SpawnCastingEffectActor(const FVector& SpawnPosition)
{
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	AActor* SpawnedEffect = CachedWorld->SpawnActor(CastEffectToSpawn, &SpawnPosition, &AbilityRotation, SpawnParams);
}

void USkillBase::ChangeRotator(const float ZOffsetAngle)
{
	AbilityRotation.Yaw += ZOffsetAngle;
}

FVector USkillBase::CalculateMaxRangeSpawn(const FVector& MousePosition, const FVector& PlayerPosition)
{
	FVector Direction = MousePosition - PlayerPosition;
	Direction.Normalize();
	const FVector MaxRangePosition = FVector(Direction.X * AbilityRange + PlayerPosition.X,
	                                         Direction.Y * AbilityRange + PlayerPosition.Y, MousePosition.Z);
	if (FVector::Distance(MousePosition, PlayerPosition) > AbilityRange)
	{
		return MaxRangePosition;
	}
	return MousePosition;
}
