// Fill out your copyright notice in the Description page of Project Settings.


#include "SpeedBuff.h"

void USpeedBuff::OnBuffBegin(UStatsComponent* StatsComponent)
{
	Activated = true;
	Timer = Time;
	StatsComponent->Haste(Amount);
}

void USpeedBuff::OnBuffTick(float DeltaTime)
{
	if(Timer > 0)
	{
		Timer -= DeltaTime;
	}else
	{
		Timer = 0;
	}
}

void USpeedBuff::OnBuffEnd(UStatsComponent* StatsComponent)
{
	StatsComponent->Haste(-Amount);
}
