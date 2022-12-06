// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Buff.h"

/**
 * 
 */
class ZINIAXWARRIORS_API FBuffFactory
{
public:

	template <typename T>
	static IBuff* CreateBuff(const float TimeAmount,const float BuffAmount)
	{
		T* NewBuff = NewObject<T>();
		IBuff* Buff = Cast<IBuff>(NewBuff);
		Buff->SetTime(TimeAmount);
		Buff->SetAmount(BuffAmount);
		return Buff;
	}
};
