// Fill out your copyright notice in the Description page of Project Settings.


#include "PowerBuff.h"


void UPowerBuff::OnBuffBegin(UStatsComponent* StatsComponent)
{
	Activated = true;
	Timer = Time;
	StatsComponent->ChangePower(Amount);
}

void UPowerBuff::OnBuffTick()
{
}

void UPowerBuff::OnBuffEnd(UStatsComponent* StatsComponent)
{
	StatsComponent->ChangePower(-Amount);
}
