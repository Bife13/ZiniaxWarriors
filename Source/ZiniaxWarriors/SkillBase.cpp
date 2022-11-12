// Fill out your copyright notice in the Description page of Project Settings.


#include "SkillBase.h"

void USkillBase::InitializeSkill(APawn* Pawn, UWorld* World)
{
	OwnerPawn = Pawn;
	CachedWorld = World;
	OnInitialize();
}

void USkillBase::UseSkill(FVector& SkillInstanceLocation, FRotator& SkillInstanceRotation)
{
	if (bCanUse)
	{
		AbilityPosition = SkillInstanceLocation;
		AbilityRotation = SkillInstanceRotation;
		bCanUse = false;
		OnUse();
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
	GetWorld()->GetTimerManager().SetTimer(THandle, this, &USkillBase::ResetCooldown, Delay, false);
}

void USkillBase::ResetCooldown()
{
	bCanUse = true;
	GEngine->AddOnScreenDebugMessage(1, 2, FColor::Green, "Reset");
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
