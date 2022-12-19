// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PassiveBase.h"
#include "ZerherPassive.generated.h"

/**
 * 
 */
UCLASS()
class ZINIAXWARRIORS_API UZerherPassive : public UPassiveBase
{
	GENERATED_BODY()

	UFUNCTION(Server, Unreliable)
	virtual void OnTick(float DeltaTime) override;


	virtual void OnHit() override;
	virtual float CheckDistance(float Damage, APawn* Owner, APawn* Target) override;

	UPROPERTY(Replicated)
    float Timer = 15;
    UPROPERTY(Replicated)
	float Cooldown = 15;
	float ShieldForce = 0.2;
};
