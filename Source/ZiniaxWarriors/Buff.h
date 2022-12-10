// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Buffable.h"
#include "StatsComponent.h"
#include "UObject/Interface.h"
#include "Buff.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UBuff : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class ZINIAXWARRIORS_API IBuff
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION()
	virtual void OnBuffBegin(UStatsComponent* StatsComponent) = 0;
	UFUNCTION()
	virtual void OnBuffTick(float DeltaTime) = 0;
	UFUNCTION()
	virtual void OnBuffEnd(UStatsComponent* StatsComponent) = 0;

	UFUNCTION()
	virtual bool GetActivated() = 0;
	UFUNCTION()
	virtual float GetTimer() = 0;

	virtual void SetTime(const float Value) = 0;
	virtual void SetAmount(const float Value) = 0;
	

};
