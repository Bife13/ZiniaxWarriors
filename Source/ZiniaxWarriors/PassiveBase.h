// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Passive.h"
#include "PassiveBase.generated.h"

/**
 * 
 */
UCLASS()
class ZINIAXWARRIORS_API UPassiveBase : public UObject , public IPassive
{
	GENERATED_BODY()
public :
	virtual void OnHit() override;
	//virtual void CheckDistance(float* Damage, APawn* Onwer,APawn* ) override;
	virtual void InitializePassive(IBuffable* OwnerCharacter) override;
protected:
	IBuffable* PassiveOwner;
};
