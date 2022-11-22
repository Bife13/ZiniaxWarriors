// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Buff.h"
#include "UObject/NoExportTypes.h"
#include "ResistanceBuff.generated.h"

/**
 * 
 */
UCLASS()
class ZINIAXWARRIORS_API UResistanceBuff : public UObject, public IBuff
{
	
	GENERATED_BODY()

	virtual void OnBuffBegin() override;
	virtual void OnBuffTick() override;
	virtual void OnBuffEnd() override;

	virtual bool GetActivated() override { return Activated; }
	virtual float GetTime() override { return Time; }
	virtual float GetAmount() override { return Amount;}
	virtual float GetTimer() override { return Timer;}
	
	virtual void SetTimer(float Value) override { Timer = Value; }
	virtual void SetTime(float Value) override { Time = Value; }
	virtual void SetAmount(float Value) override { Amount = Value; }


protected:
	float Time = 0;
	float Amount = 0;
	bool Activated = false;
	float Timer = 0;
	
};
