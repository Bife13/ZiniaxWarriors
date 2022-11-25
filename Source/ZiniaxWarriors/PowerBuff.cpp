// Fill out your copyright notice in the Description page of Project Settings.


#include "PowerBuff.h"


void UPowerBuff::OnBuffBegin(UStatsComponent* StatsComponent)
{
	Activated = true;
	Timer = Time;
	StatsComponent->Enrage(Amount);
}

void UPowerBuff::OnBuffTick(float DeltaTime)
{
	if(Timer > 0)
	{
		Timer -= DeltaTime;
	}else
	{
		Timer = 0;
	}
}

void UPowerBuff::OnBuffEnd(UStatsComponent* StatsComponent)
{
	StatsComponent->Enrage(-Amount);
}
