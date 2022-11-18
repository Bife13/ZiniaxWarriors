// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UsableCharacterSkillSlot.h"
#include "UsableSkill.h"
#include "UObject/NoExportTypes.h"
#include "SkillBase.generated.h"


UCLASS(Blueprintable)
class ZINIAXWARRIORS_API USkillBase : public UObject, public IUsableSkill
{
public:
	GENERATED_BODY()

	virtual void InitializeSkill(ACharacter* Playable, UWorld* World, int Team) override;
	UFUNCTION(BlueprintCallable)
	virtual void UseSkill() override;
	virtual void CastSkill(UAnimMontage* AnimationToPlay) override;

	// UFUNCTION(BlueprintCallable, Category = Test)
	// void StartCooldownTimer();
	// UFUNCTION(BlueprintCallable, Category = Test)
	// void StartCastTimer();

	UFUNCTION(BlueprintCallable, Category = Test)
	void ResetCooldown();

	UFUNCTION(BlueprintImplementableEvent)
	void OnCast();
	UFUNCTION(BlueprintImplementableEvent)
	void OnUse();
	UFUNCTION(BlueprintImplementableEvent)
	void OnInitialize();

	UPROPERTY(BlueprintReadWrite, EditInstanceOnly)
	float AbilityCooldown;
	UFUNCTION(BlueprintCallable)
	void SetCooldown(float Cooldown);

	UPROPERTY(BlueprintReadWrite, EditInstanceOnly)
	float AbilityCastTime;
	UFUNCTION(BlueprintCallable)
	void SetCastTime(float CastTime);

	UPROPERTY(BlueprintReadWrite, EditInstanceOnly)
	float AbilityDamage;
	UFUNCTION(BlueprintCallable)
	void SetAbilityDamage(float Power, float AbilityPower);

	UPROPERTY(BlueprintReadWrite, EditInstanceOnly)
	float AbilityRange;
	UFUNCTION(BlueprintCallable)
	void SetAbilityRange(float Range);

	UPROPERTY(BlueprintReadWrite)
	bool bCanUse = true;

	UPROPERTY(BlueprintReadWrite)
	ACharacter* OwnerCharacter;
	UPROPERTY(BlueprintReadWrite)
	UWorld* CachedWorld;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite)
	TSubclassOf<AActor> ActorToSpawn;
	UPROPERTY(BlueprintReadWrite)
	FRotator AbilityRotation;

	UPROPERTY(BlueprintReadWrite)
	UAnimMontage* AttackAnimation;

	UFUNCTION(BlueprintCallable)
	int GetTeamId() const { return TeamId; }

	IUsableCharacterSkillSlot* CachedCharacterInterface;
protected:
	UFUNCTION(BlueprintCallable)
	void SpawnSkillActor(const FVector& SpawnPosition);
	UFUNCTION(BlueprintCallable)
	void ChangeRotator(const float ZOffsetAngle);
	UPROPERTY()
	int TeamId;
};
