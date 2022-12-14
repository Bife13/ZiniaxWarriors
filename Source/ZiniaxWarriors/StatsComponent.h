// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HealthSystem.h"
#include "Components/ActorComponent.h"
#include "StatsComponent.generated.h"


//AttackPower Buff/Debuff events
DECLARE_EVENT_OneParam(UStatsComponent, EnrageAppliedEvent, float)

DECLARE_EVENT_OneParam(UStatsComponent, EnrageRemovedEvent, float)

DECLARE_EVENT_OneParam(UStatsComponent, WeakenAppliedEvent, float)

DECLARE_EVENT_OneParam(UStatsComponent, WeakenRemovedEvent, float)

//Defense Buff/Debuff events
DECLARE_EVENT_OneParam(UStatsComponent, BulkAppliedEvent, float)

DECLARE_EVENT_OneParam(UStatsComponent, BulkRemovedEvent, float)

DECLARE_EVENT_OneParam(UStatsComponent, VulnerableAppliedEvent, float)

DECLARE_EVENT_OneParam(UStatsComponent, VulnerableRemovedEvent, float)

//Speed Buff/Debuff events
DECLARE_EVENT_OneParam(UStatsComponent, SlowAppliedEvent, float)

DECLARE_EVENT_OneParam(UStatsComponent, HasteAppliedEvent, float)

DECLARE_EVENT_OneParam(UStatsComponent, SlowRemovedEvent, float)

DECLARE_EVENT_OneParam(UStatsComponent, HasteRemovedEvent, float)

//Root Debuff events
DECLARE_EVENT(UStatsComponent, RootAppliedEvent)

DECLARE_EVENT(UStatsComponent, RootRemoveEvent)

//Shield Buff events
DECLARE_EVENT_OneParam(UStatsComponent, ShieldAppliedEvent, float);

DECLARE_EVENT_OneParam(UStatsComponent, ShieldRemovedEvent, float);

//Casting Slow events
DECLARE_EVENT_OneParam(UStatsComponent, CastingSlowRemovedEvent, float)

DECLARE_EVENT_OneParam(UStatsComponent, CastingSlowAppliedEvent, float)

//UI Stuff
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FApllyBuffEvent, FString, NameOfBuff, bool, IsBuff, int, BuffIndex);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FRemoveBuffEvent, FString, NameOfBuff, bool, IsBuff, int, BuffIndex);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class ZINIAXWARRIORS_API UStatsComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UStatsComponent();
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
	UFUNCTION(BlueprintCallable)
	float GetSpeed() const { return CurrentSpeed; }

	UFUNCTION(BlueprintCallable)
	float GetPower() const { return CurrentPower; }

	UFUNCTION(BlueprintCallable)
	float GetMaximumHealth() const { return CurrentMaximumHealth; }

	UFUNCTION(BlueprintCallable)
	float GetResistance() const { return CurrentResistance; }

	UFUNCTION(BlueprintCallable)
	float GetViewRange() const { return CurrentViewRange; }

	UFUNCTION(BlueprintCallable)
	float GetShield() const { return CurrentShield; }

	UFUNCTION()
	void Enrage(float Amount);
	EnrageAppliedEvent OnEnrageAppliedEvent;
	EnrageRemovedEvent OnEnrageRemovedEvent;

	UFUNCTION()
	void Weaken(float Amount);
	WeakenAppliedEvent OnWeakenAppliedEvent;
	WeakenRemovedEvent OnWeakenRemovedEvent;

	UFUNCTION()
	void Bulk(float Amount);
	BulkAppliedEvent OnBulkAppliedEvent;
	BulkRemovedEvent OnBulkRemovedEvent;

	UFUNCTION()
	void Vulnerable(float Amount);
	VulnerableAppliedEvent OnVulnerableAppliedEvent;
	VulnerableRemovedEvent OnVulnerableRemovedEvent;
	UFUNCTION(NetMulticast, Reliable)
	void HandleVulnerableEvents(float Amount);

	UFUNCTION()
	void Haste(float Amount);
	UFUNCTION()
	void HasteRemove(float Amount);
	HasteAppliedEvent OnHasteAppliedEvent;
	HasteRemovedEvent OnHasteRemovedEvent;

	UFUNCTION()
	void Slow(float Amount);
	UFUNCTION()
	void SlowRemove(float Amount);
	SlowAppliedEvent OnSlowAppliedEvent;
	SlowRemovedEvent OnSlowRemovedEvent;

	UFUNCTION()
	void Root();
	UFUNCTION()
	void EndRoot(float Amount);
	RootAppliedEvent OnRootApplied;
	RootRemoveEvent OnRootRemoved;

	UFUNCTION()
	void Shield(float Amount);
	UFUNCTION()
	void RemoveShield(float Amount);
	ShieldAppliedEvent OnShieldApplied;
	ShieldRemovedEvent OnShieldRemoved;

	UFUNCTION()
	void CastingSlow(float Amount);
	UFUNCTION()
	void RemoveCastingSlow(float Amount);
	CastingSlowAppliedEvent OnCastingSlowApplied;
	CastingSlowRemovedEvent OnCastingSlowRemovedEvent;

	// FORCEINLINE void SetSpeed(float Value) { Speed = Value; }
	// FORCEINLINE void SetPower(float Value) { Power = Value; }
	// FORCEINLINE void SetMaximumHealth(float Value) { MaximumHealth = Value; }
	// FORCEINLINE void SetResistance(float Value) { Resistance = Value; }
	// FORCEINLINE void SetViewRange(float Value) { ViewRange = Value; }

	UFUNCTION(NetMulticast, Reliable)
	void SetupStatSystem(float PowerValue, float SpeedValue, float MaximumHealthValue, float ResistanceValue,
	                     float ViewRangeValue);


	UPROPERTY(BlueprintAssignable)
	FApllyBuffEvent BuffApllied;

	UPROPERTY(BlueprintAssignable)
	FRemoveBuffEvent BuffRemove;

protected:
	// Called when the game starts
	UFUNCTION()
	virtual void BeginPlay() override;
	UPROPERTY()
	float BasePower;
	UPROPERTY()
	float BaseSpeed;
	UPROPERTY()
	float BaseMaximumHealth;
	UPROPERTY()
	float BaseResistance;
	UPROPERTY()
	float BaseViewRange;

	UPROPERTY()
	UHealthSystem* HealthSystem;

	UPROPERTY(Replicated, VisibleAnywhere)
	float CurrentPower;
	UPROPERTY(Replicated, VisibleAnywhere)
	float CurrentSpeed;
	UPROPERTY(Replicated, VisibleAnywhere)
	float CurrentMaximumHealth;
	UPROPERTY(Replicated, VisibleAnywhere)
	float CurrentResistance;
	UPROPERTY(Replicated, VisibleAnywhere)
	float CurrentViewRange;
	UPROPERTY(Replicated, VisibleAnywhere)
	float CurrentShield;
};
