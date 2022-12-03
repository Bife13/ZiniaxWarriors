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
DECLARE_EVENT_OneParam(UStatsComponent, ShieldAppliedEvent,float);
DECLARE_EVENT_OneParam(UStatsComponent, ShieldRemovedEvent,float);
//Casting Slow events
DECLARE_EVENT_OneParam(UStatsComponent, CastingSlowRemovedEvent, float)
DECLARE_EVENT_OneParam(UStatsComponent, CastingSlowAppliedEvent, float)

//UI Stuff
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FApllyBuffEvent,FString,NameOfBuff,bool,IsBuff,int,BuffIndex);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FRemoveBuffEvent,FString,NameOfBuff,bool,IsBuff,int,BuffIndex);

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
	float GetShield() const {return CurrentShield;}

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
	void HasteRemove(float Amount);
	HasteAppliedEvent OnHasteAppliedEvent;
    HasteRemovedEvent OnHasteRemovedEvent;
	
	void Slow(float Amount);
	void SlowRemove(float Amount);
	SlowAppliedEvent OnSlowAppliedEvent;
	SlowRemovedEvent OnSlowRemovedEvent;

	void Root();
	void EndRoot(float Amount);
	RootAppliedEvent OnRootApplied;
	RootRemoveEvent OnRootRemoved;

	void Shield(float Amount);
	void RemoveShield(float Amount);
	ShieldAppliedEvent OnShieldApplied;
	ShieldRemovedEvent OnShieldRemoved;

	void CastingSlow(float Amount);
	void RemoveCastingSlow(float Amount);
	CastingSlowAppliedEvent OnCastingSlowApplied;
	CastingSlowRemovedEvent OnCastingSlowRemovedEvent;
	
	// FORCEINLINE void SetSpeed(float Value) { Speed = Value; }
	// FORCEINLINE void SetPower(float Value) { Power = Value; }
	// FORCEINLINE void SetMaximumHealth(float Value) { MaximumHealth = Value; }
	// FORCEINLINE void SetResistance(float Value) { Resistance = Value; }
	// FORCEINLINE void SetViewRange(float Value) { ViewRange = Value; }

	void SetupStatSystem(float PowerValue, float SpeedValue, float MaximumHealthValue, float ResistanceValue,
	                     float ViewRangeValue);


	UPROPERTY(BlueprintAssignable)
	FApllyBuffEvent BuffApllied;

	UPROPERTY(BlueprintAssignable)
	FRemoveBuffEvent BuffRemove;
    
protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	float BasePower;
	float BaseSpeed;
	float BaseMaximumHealth;
	float BaseResistance;
	float BaseViewRange;

	UPROPERTY()
	UHealthSystem* HealthSystem;
	
	float CurrentPower;
	float CurrentSpeed;
	float CurrentMaximumHealth;
	float CurrentResistance;
	float CurrentViewRange;
	float CurrentShield;
};
