// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Buffable.h"
#include "UObject/Interface.h"
#include "Passive.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI,Blueprintable)
class UPassive : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class ZINIAXWARRIORS_API IPassive
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void OnHit() = 0;
	virtual float CheckDistance(float Damage,APawn* Owner,APawn* Target) = 0;
	virtual void InitializePassive(IBuffable* OwnerCharacter) = 0;
};
