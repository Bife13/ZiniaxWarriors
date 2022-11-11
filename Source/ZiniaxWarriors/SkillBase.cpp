// Fill out your copyright notice in the Description page of Project Settings.


#include "SkillBase.h"

void USkillBase::InitializeSkill(APawn* Pawn, UWorld* World)
{
	OwnerPawn = Pawn;
	OnInitialize();
}

void USkillBase::UseSkill(FVector& SkillInstanceLocation, float& ZDirection)
{
	OnUse();
}

void USkillBase::SetCooldown(float Amount)
{
	Cooldown = Amount;
}

