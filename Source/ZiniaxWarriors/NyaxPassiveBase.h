// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PassiveBase.h"
#include "NyaxPassiveBase.generated.h"

/**
 * 
 */
UCLASS()
class ZINIAXWARRIORS_API UNyaxPassiveBase : public UPassiveBase
{
	GENERATED_BODY()
public:
	virtual void OnHit() override;

	float Time = 1;
	float Amount = 0.5;
};
