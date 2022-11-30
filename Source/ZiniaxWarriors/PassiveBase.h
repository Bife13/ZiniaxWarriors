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
	virtual float CheckDistance(float Damage, APawn* Owner,APawn* target) override;
	virtual void InitializePassive(IBuffable* OwnerCharacter) override;
	virtual void OnTick(float DeltaTime) override;
protected:
	IBuffable* PassiveOwner;
};
