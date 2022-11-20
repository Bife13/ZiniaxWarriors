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
	FBuffFactory();
	~FBuffFactory();

	static IBuff* GetBuff(FString BuffName);

	template <typename T>
	static IBuff* CreateBuff()
	{
		T* NewBuff = NewObject<T>();
		return Cast<IBuff>(NewBuff);
	}
};
