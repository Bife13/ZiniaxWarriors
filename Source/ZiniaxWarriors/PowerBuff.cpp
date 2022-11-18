// Fill out your copyright notice in the Description page of Project Settings.


#include "PowerBuff.h"

void UPowerBuff::OnBuffBegin()
{
	GEngine->AddOnScreenDebugMessage(1, 2, FColor::White, "Applied Buff");
}

void UPowerBuff::OnBuffTick()
{
}

void UPowerBuff::OnBuffEnd()
{
}
