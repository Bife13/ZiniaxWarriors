// Fill out your copyright notice in the Description page of Project Settings.


#include "Bulk.h"

void UBulk::OnBuffBegin(UStatsComponent* StatsComponent)
{
	Activated = true;
	Timer = Time;
	StatsComponent->Bulk(Amount);
}

void UBulk::OnBuffTick(float DeltaTime)
{
	if(Timer > 0)
	{
		Timer -= DeltaTime;
	}else
	{
		Timer = 0;
	}
}

void UBulk::OnBuffEnd(UStatsComponent* StatsComponent)
{
	StatsComponent->Bulk(-Amount);
}
