// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UsableCharacterSkillSlot.h"
#include "UsableSkill.h"
#include "Components/Image.h"
#include "UObject/NoExportTypes.h"
#include "SkillBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FSkillCasted,float,Cooldown);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FSkillReset,bool,isReset);
UCLASS(Blueprintable)
class ZINIAXWARRIORS_API USkillBase : public UObject, public IUsableSkill
{
public:
	GENERATED_BODY()
	UFUNCTION(BlueprintCallable)
	virtual void InitializeSkill(ACharacter* Playable, UWorld* World, int Team) override;
	UFUNCTION(BlueprintCallable)
	virtual void UseSkill() override;
	virtual void CastSkill(UAnimMontage* AnimationToPlay) override;

	virtual bool IsSupportedForNetworking() const override;
	

	UFUNCTION(BlueprintCallable)
	void DelayedSpawnTimer(const FVector& SpawnPosition, float NumberOfProjectile);

	UFUNCTION()
	void DelayedSpawn(const FVector& SpawnPosition);
	
	UFUNCTION(Server,Reliable)
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
	float AbilitySpawnTime;
	UFUNCTION(BlueprintCallable)
	void SetSpawnTime(float SpawnTime);

	UPROPERTY(BlueprintReadWrite, EditInstanceOnly)
	float AbilityDamage;
	UFUNCTION(BlueprintCallable)
	void SetAbilityDamage(float Power, float AbilityPower, float AddValue);

	UPROPERTY(BlueprintReadWrite, EditInstanceOnly)
	float AbilityRange;
	UFUNCTION(BlueprintCallable)
	void SetAbilityRange(float Range);

	UPROPERTY(BlueprintReadWrite)
	bool bCanUse;

	UPROPERTY(BlueprintReadWrite)
	ACharacter* OwnerCharacter;
	UPROPERTY(BlueprintReadWrite)
	UWorld* CachedWorld;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite)
	TSubclassOf<AActor> ActorToSpawn;
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite)
	TSubclassOf<AActor> CastEffectToSpawn;
	UPROPERTY(BlueprintReadWrite)
	FRotator AbilityRotation;

	UPROPERTY(BlueprintReadWrite)
	UAnimMontage* AttackAnimation;

	UFUNCTION(BlueprintCallable)
	int GetTeamId() const { return TeamId; }

	IUsableCharacterSkillSlot* CachedCharacterInterface;
	
	UPROPERTY(BlueprintReadWrite)
    UTexture* SkillIconTexture;
	
protected:
	UFUNCTION(BlueprintCallable)
	void SpawnSkillActor(const FVector& SpawnPosition);
	UFUNCTION(BlueprintCallable)
	void SpawnCastingEffectActor(const FVector& SpawnPosition);
	UFUNCTION(BlueprintCallable)
	void ChangeRotator(const float ZOffsetAngle);
	UFUNCTION(BlueprintCallable)
	FVector CalculateMaxRangeSpawn(const FVector& MousePosition,const FVector& PlayerPosition);
	UPROPERTY()
	int TeamId;

public:
	UFUNCTION(BlueprintCallable)
	float CooldownForUi(){ return  AbilityCooldown;}

	UPROPERTY(BlueprintAssignable)
	FSkillCasted CastEvent;

	UPROPERTY(BlueprintAssignable)
	FSkillReset ResetEvent;
	
};
