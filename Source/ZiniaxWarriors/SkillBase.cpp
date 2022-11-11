// Fill out your copyright notice in the Description page of Project Settings.


#include "SkillBase.h"

void USkillBase::InitializeSkill(APawn* Pawn, UWorld* World)
{
	OnInitialize(Pawn, World);
}

void USkillBase::UseSkill(FVector& SkillInstanceLocation, float& ZDirection)
{
	OnUseSkill(SkillInstanceLocation, ZDirection);
}

void USkillBase::SetCooldown(float Amount)
{
	Cooldown = Amount;
}
