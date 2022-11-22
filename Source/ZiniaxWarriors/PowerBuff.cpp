// Fill out your copyright notice in the Description page of Project Settings.


#include "PowerBuff.h"


void UPowerBuff::OnBuffBegin(UStatsComponent* StatsComponent)
{
	GEngine->AddOnScreenDebugMessage(1, 2, FColor::White, FString::Printf(TEXT("%f"), Time));
	Activated = true;
	Timer = Time;
	StatsComponent->ChangePower(Amount);
}

void UPowerBuff::OnBuffTick()
{
}

void UPowerBuff::OnBuffEnd(UStatsComponent* StatsComponent)
{
	GEngine->AddOnScreenDebugMessage(1, 2, FColor::White, "FODASSE");
	StatsComponent->ChangePower(-Amount);
}
