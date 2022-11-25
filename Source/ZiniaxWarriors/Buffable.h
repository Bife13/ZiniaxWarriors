// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Buffable.generated.h"

UINTERFACE(MinimalAPI, meta = (CannotImplementInterfaceInBlueprint))
class UBuffable : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class ZINIAXWARRIORS_API IBuffable
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	virtual void AddPowerBuff(float TimeAmount, float BuffAmount) = 0;
	UFUNCTION(BlueprintCallable)
	virtual void AddResistanceBuff(float TimeAmount, float BuffAmount) = 0;
};
