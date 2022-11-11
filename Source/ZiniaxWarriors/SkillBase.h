// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UsableSkill.h"
#include "UObject/NoExportTypes.h"
#include "SkillBase.generated.h"

/**
 * 
 */
UCLASS()
class ZINIAXWARRIORS_API USkillBase : public UObject, public IUsableSkill
{
public:
	GENERATED_BODY()

	virtual void InitializeSkill(APawn* Pawn, UWorld* World) override;
	virtual void UseSkill(FVector& SkillInstanceLocation, float& ZDirection) override;

	UFUNCTION(BlueprintImplementableEvent)
	void OnUseSkill(FVector& SkillInstanceLocation, float& ZDirection);
	UFUNCTION(BlueprintImplementableEvent)
	void OnInitialize(APawn* Pawn, UWorld* World);

	
	UPROPERTY(BlueprintReadWrite)
	float Cooldown;
	UFUNCTION(BlueprintCallable)
	void SetCooldown(float Amount);
	
};
