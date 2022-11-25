// Fill out your copyright notice in the Description page of Project Settings.


#include "Weaken.h"


void UWeaken::OnBuffBegin(UStatsComponent* StatsComponent)
{
	Activated = true;
	Timer = Time;
	StatsComponent->Weaken(Amount);
}

void UWeaken::OnBuffTick(float DeltaTime)
{
	if(Timer > 0)
	{
		Timer -= DeltaTime;
	}else
	{
		Timer = 0;
	}
}

void UWeaken::OnBuffEnd(UStatsComponent* StatsComponent)
{
	StatsComponent->Weaken(-Amount);
}