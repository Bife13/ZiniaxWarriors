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
	virtual void OnBuffBegin(UStatsComponent* StatsComponent) = 0;
	virtual void OnBuffTick() = 0;
	virtual void OnBuffEnd(UStatsComponent* StatsComponent) = 0;

	virtual bool GetActivated() = 0;
	virtual float GetTime() = 0;
	virtual float GetAmount() = 0;
	virtual float GetTimer() = 0;
	virtual void SetTimer(float Value) = 0;

	virtual void SetTime(float Value) = 0;
	virtual void SetAmount(float Value) = 0;


};
