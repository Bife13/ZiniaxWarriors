// Fill out your copyright notice in the Description page of Project Settings.


#include "BuffFactory.h"
#include "PowerBuff.h"

BuffFactory::BuffFactory()
{
}

BuffFactory::~BuffFactory()
{
}

IBuff* BuffFactory::GetBuff(FString BuffType)
{
	if (BuffType == "PowerBuff")
	{
		UPowerBuff* PowerBuff = NewObject<UPowerBuff>();
		return PowerBuff;
	}
	return NULL;
}
