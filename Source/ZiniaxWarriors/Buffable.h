// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FunctionalTestUtilityLibrary.h"
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
	virtual void AddEnrage(float TimeAmount, float BuffAmount) = 0;
	UFUNCTION(BlueprintCallable)
	virtual void AddBulk(float TimeAmount, float BuffAmount) = 0;
	UFUNCTION(BlueprintCallable)
	virtual void AddHaste(float TimeAmount, float BuffAmount) = 0;
	UFUNCTION(BlueprintCallable)
	virtual void AddVulnerable(float TimeAmount, float DebuffAmount) = 0;
	UFUNCTION(BlueprintCallable)
	virtual void AddWeaken(float TimeAmount, float DebuffAmount) = 0;
	UFUNCTION(BlueprintCallable)
	virtual void AddSlow(float TimeAmount, float DebuffAmount) = 0;
	UFUNCTION(BlueprintCallable)
	virtual void AddRoot(float TimeAmount) = 0;
	UFUNCTION(BlueprintCallable)
	virtual void AddShield(float TimeAmount,float BuffAmount) = 0;
	UFUNCTION(BlueprintCallable)
	virtual void AddCastingSlow(float TimeAmount,float BuffAmount) = 0;
};
