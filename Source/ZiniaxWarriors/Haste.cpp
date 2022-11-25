// Fill out your copyright notice in the Description page of Project Settings.


#include "Haste.h"

void UHaste::OnBuffBegin(UStatsComponent* StatsComponent)
{
	Activated = true;
	Timer = Time;
	StatsComponent->Haste(Amount);
}

void UHaste::OnBuffTick(float DeltaTime)
{
	if(Timer > 0)
	{
		Timer -= DeltaTime;
	}else
	{
		Timer = 0;
	}
}

void UHaste::OnBuffEnd(UStatsComponent* StatsComponent)
{
	StatsComponent->HasteRemove(TemporarySpeed);
}
