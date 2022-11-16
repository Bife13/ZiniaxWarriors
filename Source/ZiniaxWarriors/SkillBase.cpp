// Fill out your copyright notice in the Description page of Project Settings.


#include "SkillBase.h"
#include "PlayableCharacter.h"
#include "Components/DecalComponent.h"

void USkillBase::InitializeSkill(ACharacter* Playable, UWorld* World,int Team)
{
	OwnerCharacter = Playable;
	CachedWorld = World;
	TeamId = Team;
	CachedCharacterInterface = Cast<IUsableCharacterSkillSlot>(OwnerCharacter);
	OnInitialize();
}


void USkillBase::CastSkill(UAnimMontage* AnimationToPlay)
{
	if (bCanUse)
	{
		CachedCharacterInterface->SetIsCasting(true);
		AttackAnimation = AnimationToPlay;
		bCanUse = false;
		OnCast();
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(1, 2, FColor::Red, "On Cooldown");
	}
}


// void USkillBase::StartCooldownTimer()
// {
// 	FTimerHandle THandle;
// 	const float Delay = AbilityCooldown;
// 	CachedWorld->GetTimerManager().SetTimer(THandle, this, &USkillBase::ResetCooldown, Delay, false);
// }
//
// void USkillBase::StartCastTimer()
// {
// 	FTimerHandle THandle;
// 	const float Delay = AbilityCastTime;
// 	CachedWorld->GetTimerManager().SetTimer(THandle, this, &USkillBase::UseSkill, Delay, false);
// }

void USkillBase::ResetCooldown()
{
	bCanUse = true;
	GEngine->AddOnScreenDebugMessage(1, 2, FColor::Green, "Reset");
}

void USkillBase::UseSkill()
{
	const APlayableCharacter* PlayableCharacter = Cast<APlayableCharacter>(OwnerCharacter);
	AbilityRotation = PlayableCharacter->CalculateLookingDirection();
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

void USkillBase::SetAbilityDamage(const float Power, float AbilityPower)
{
	AbilityDamage = Power * AbilityPower;
}


AActor* USkillBase::SpawnSkillActor(const FVector& SpawnPosition)
{
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	AActor* SpawnedAbility = CachedWorld->SpawnActor(ActorToSpawn, &SpawnPosition, &AbilityRotation, SpawnParams);
	return SpawnedAbility;
}
