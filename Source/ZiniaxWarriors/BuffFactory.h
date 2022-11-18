// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Buff.h"

/**
 * 
 */
class ZINIAXWARRIORS_API BuffFactory
{
public:
	BuffFactory();
	~BuffFactory();

	IBuff* GetBuff(FString BuffType);
};
