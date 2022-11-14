// Fill out your copyright notice in the Description page of Project Settings.


#include "SkillBase.h"
#include "PlayableCharacter.h"
#include "Components/DecalComponent.h"

void USkillBase::InitializeSkill(ACharacter* Playable, UWorld* World)
{
	OwnerCharacter = Playable;
	CachedWorld = World;
	CachedCharacterInterface = Cast<IUsableCharacterSkillSlot>(OwnerCharacter);
	OnInitialize();
}


void USkillBase::CastSkill(UAnimMontage* AnimationToPlay)
{
	if (bCanUse && !CachedCharacterInterface->GetIsCasting())
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


void USkillBase::StartCooldownTimer()
{
	FTimerHandle THandle;
	const float Delay = Cooldown;
	CachedWorld->GetTimerManager().SetTimer(THandle, this, &USkillBase::ResetCooldown, Delay, false);
}

void USkillBase::StartCastTimer()
{
	FTimerHandle THandle;
	const float Delay = 1;
	CachedWorld->GetTimerManager().SetTimer(THandle, this, &USkillBase::UseSkill, Delay, false);
}

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

void USkillBase::SetCooldown(float Amount)
{
	Cooldown = Amount;
}

void USkillBase::SpawnSkillActor(const FVector& SpawnPosition)
{
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	CachedWorld->SpawnActor(ActorToSpawn, &SpawnPosition, &AbilityRotation, SpawnParams);
}
