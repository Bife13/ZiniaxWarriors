// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HealthSystem.h"
#include "Components/ActorComponent.h"
#include "StatsComponent.generated.h"


DECLARE_EVENT_OneParam(UStatsComponent, PowerChangedEvent, float)
DECLARE_EVENT_OneParam(UStatsComponent, ResistanceChangedEvent, float)
DECLARE_EVENT_OneParam(UStatsComponent, SpeedChangedEvent, float)


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

	float GetSpeed() const { return CurrentSpeed; }

	UFUNCTION(BlueprintCallable)

	float GetPower() const { return CurrentPower; }
	float GetMaximumHealth() const { return CurrentMaximumHealth; }
	float GetResistance() const { return CurrentResistance; }
	float GetViewRange() const { return CurrentViewRange; }

	
	void ChangePower(float Amount);
	PowerChangedEvent OnPowerChangedEvent;

	void ChangeResistance(float Amount);
	ResistanceChangedEvent OnResistanceChangedEvent;

	void ChangeSpeed(float Amount);
	SpeedChangedEvent OnSpeedChangedEvent;

    void Enrage(float Amount);
	EnrageAppliedEvent OnEnrageAppliedEvent;
	EnrageRemovedEvent OnEnrageRemovedEvent;
	
	void Weaken(float Amount);
    WeakenAppliedEvent OnWeakenAppliedEvent;
	WeakenRemovedEvent OnWeakenRemovedEvent;

	void Bulk(float Amount);
	BulkAppliedEvent OnBulkAppliedEvent;
	BulkRemovedEvent OnBulkRemovedEvent;

	void Vulnerable(float Amount);
	VulnerableAppliedEvent OnVulnerableAppliedEvent;
	VulnerableRemovedEvent OnVulnerableRemovedEvent;
	
	void Haste(float Amount);
	HasteAppliedEvent OnHasteAppliedEvent;
    HasteRemovedEvent OnHasteRemovedEvent;
	
	void Slow(float Amount);
	SlowAppliedEvent OnSlowAppliedEvent;
	SlowRemovedEvent OnSlowRemovedEvent;


	// FORCEINLINE void SetSpeed(float Value) { Speed = Value; }
	// FORCEINLINE void SetPower(float Value) { Power = Value; }
	// FORCEINLINE void SetMaximumHealth(float Value) { MaximumHealth = Value; }
	// FORCEINLINE void SetResistance(float Value) { Resistance = Value; }
	// FORCEINLINE void SetViewRange(float Value) { ViewRange = Value; }

	void SetupStatSystem(float PowerValue, float SpeedValue, float MaximumHealthValue, float ResistanceValue,
	                     float ViewRangeValue);

    
protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	float BasePower;
	float BaseSpeed;
	float BaseMaximumHealth;
	float BaseResistance;
	float BaseViewRange;

	float CurrentPower;
	float CurrentSpeed;
	float CurrentMaximumHealth;
	float CurrentResistance;
	float CurrentViewRange;
	UPROPERTY()
	UHealthSystem* HealthSystem;
};
