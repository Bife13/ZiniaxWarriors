// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PassiveBase.h"
#include "DrexPassive.generated.h"

/**
 * 
 */
UCLASS()
class ZINIAXWARRIORS_API UDrexPassive : public UPassiveBase
{
	GENERATED_BODY()
	virtual float CheckDistance(float Damage, APawn* Owner, APawn* Target) override;

	virtual void OnTick(float DeltaTime) override;

	virtual void OnHit() override;
	float TolerationDistance = 400;
	float DamageChange = 0.15;
};
