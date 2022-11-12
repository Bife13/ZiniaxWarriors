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
	AbilityPosition = SkillInstanceLocation;
	AbilityRotation = SkillInstanceRotation;
	SpawnSkillActor(*CachedWorld, AbilityPosition, AbilityRotation);
	OnUse();
}

void USkillBase::SetCooldown(float Amount)
{
	Cooldown = Amount;
}

void USkillBase::SpawnSkillActor(UWorld& World, const FVector& SpawnPosition, const FRotator& SpawnRotation) const
{
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	World.SpawnActor(ActorToSpawn, &SpawnPosition, &SpawnRotation, SpawnParams);
}
