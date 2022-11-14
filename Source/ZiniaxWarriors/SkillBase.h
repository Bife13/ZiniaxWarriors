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
	UFUNCTION(BlueprintCallable)
	virtual void UseSkill() override;
	virtual void CastSkill(UAnimMontage* AnimationToPlay) override;

	UFUNCTION(BlueprintCallable, Category = Test)
	void StartCooldownTimer();
	UFUNCTION(BlueprintCallable, Category = Test)
	void StartCastTimer();

	void ResetCooldown();

	UFUNCTION(BlueprintImplementableEvent)
	void OnCast();
	UFUNCTION(BlueprintImplementableEvent)
	void OnUse();
	UFUNCTION(BlueprintImplementableEvent)
	void OnInitialize();

	UPROPERTY(BlueprintReadWrite, EditInstanceOnly)
	float Cooldown;
	UFUNCTION(BlueprintCallable)
	void SetCooldown(float Amount);

	UPROPERTY(BlueprintReadWrite)
	bool bCanUse = true;

	UPROPERTY(BlueprintReadWrite)
	APawn* OwnerPawn;
	UPROPERTY(BlueprintReadWrite)
	UWorld* CachedWorld;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite)
	TSubclassOf<AActor> ActorToSpawn;
	UPROPERTY(BlueprintReadWrite)
	FVector AbilityPosition;
	UPROPERTY(BlueprintReadWrite)
	FRotator AbilityRotation;

	UPROPERTY(BlueprintReadWrite)
	UAnimMontage* AttackAnimation;


protected:
	UFUNCTION(BlueprintCallable)
	void SpawnSkillActor(const FVector& SpawnPosition);
};
