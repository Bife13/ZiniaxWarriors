// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SkillBase.h"
#include "Engine/DataTable.h"

#include "DTR_SkillsDatatable.generated.h"


USTRUCT(Blueprintable)
struct FSkillsDatatable : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<USkillBase> Skill;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FString Description;
};
