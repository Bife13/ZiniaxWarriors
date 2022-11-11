// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UsableSkill.h"
#include "UObject/NoExportTypes.h"
#include "SkillBase.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class ZINIAXWARRIORS_API USkillBase : public UObject, public IUsableSkill
{
public:
	GENERATED_BODY()

	virtual void InitializeSkill(APawn* Pawn, UWorld* World) override;
	virtual void UseSkill(FVector& SkillInstanceLocation, float& ZDirection) override;

	UFUNCTION(BlueprintImplementableEvent)
	void OnUse();

	UFUNCTION(BlueprintImplementableEvent)
	void OnInitialize();


	UPROPERTY(BlueprintReadWrite)
	float Cooldown;
	UFUNCTION(BlueprintCallable)
	void SetCooldown(float Amount);

	UPROPERTY(BlueprintReadWrite)
	APawn* OwnerPawn;
	
};
