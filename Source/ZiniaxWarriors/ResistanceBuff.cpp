// Fill out your copyright notice in the Description page of Project Settings.


#include "ResistanceBuff.h"

void UResistanceBuff::OnBuffBegin(UStatsComponent* StatsComponent)
{
	Activated = true;
	Timer = Time;
	StatsComponent->ChangeResistance(Amount);
}

void UResistanceBuff::OnBuffTick(float DeltaTime)
{
	if(Timer > 0)
	{
		Timer -= DeltaTime;
	}else
	{
		Timer = 0;
	}
}

void UResistanceBuff::OnBuffEnd(UStatsComponent* StatsComponent)
{
	StatsComponent->ChangeResistance(-Amount);
}
