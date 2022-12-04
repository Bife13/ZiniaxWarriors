// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PassiveBase.h"
#include "NyaxPassive.generated.h"

/**
 * 
 */
UCLASS()
class ZINIAXWARRIORS_API UNyaxPassive : public UPassiveBase
{
	GENERATED_BODY()
public:
	virtual void OnHit() override;

	virtual float CheckDistance(float Damage, APawn* Owner, APawn* Target) override;

    virtual void OnTick(float DeltaTime) override;

	float Time = 1;
	float Amount = 0.15;
};
