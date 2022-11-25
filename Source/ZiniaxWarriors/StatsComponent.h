// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HealthSystem.h"
#include "Components/ActorComponent.h"
#include "StatsComponent.generated.h"

DECLARE_EVENT_OneParam(UStatsComponent, PowerChangedEvent, float)
DECLARE_EVENT_OneParam(UStatsComponent, ResistanceChangedEvent, float)
DECLARE_EVENT_OneParam(UStatsComponent, SpeedChangedEvent, float)

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
