// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "StatsComponent.generated.h"


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

	float GetSpeed() const { return Speed; }
	float GetMaximumHealth() const { return MaximumHealth; }
	float GetResistance() const { return Resistance; }
	float GetViewRange() const { return ViewRange; }

	FORCEINLINE void SetSpeed(float Value) { Speed = Value; }
	FORCEINLINE void SetMaximumHealth(float Value) { MaximumHealth = Value; }
	FORCEINLINE void SetResistance(float Value) { Resistance = Value; }
	FORCEINLINE void SetViewRange(float Value) { ViewRange = Value; }

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	float Speed;
	float MaximumHealth;
	float Resistance;
	float ViewRange;
};
