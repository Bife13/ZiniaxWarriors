// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Buff.h"
#include "UObject/NoExportTypes.h"
#include "PowerBuff.generated.h"

/**
 * 
 */
UCLASS()
class ZINIAXWARRIORS_API UPowerBuff : public UObject, public IBuff
{
	GENERATED_BODY()

	virtual void OnBuffBegin() override;
	virtual void OnBuffTick() override;
	virtual void OnBuffEnd() override;
};
