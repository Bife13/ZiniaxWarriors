// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Buff.h"
#include "UObject/NoExportTypes.h"
#include "Shield.generated.h"

/**
 * 
 */
UCLASS()
class ZINIAXWARRIORS_API UShield : public UObject, public IBuff
{
	GENERATED_BODY()
	virtual void OnBuffBegin(UStatsComponent* StatsComponent) override;
	virtual void OnBuffTick(float DeltaTime) override;
	virtual void OnBuffEnd(UStatsComponent* StatsComponent) override;

	virtual bool GetActivated() override { return Activated; }
	virtual float GetTimer() override { return Timer; }
	
	virtual void SetTime(const float Value) override { Time = Value; }
	virtual void SetAmount(const float Value) override { Amount = Value; }

	float Time = 0;
	float Amount = 0;
	bool Activated = false;
	float Timer = 0;
};
