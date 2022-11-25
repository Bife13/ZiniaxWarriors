// Fill out your copyright notice in the Description page of Project Settings.


#include "Slow.h"

void USlow::OnBuffBegin(UStatsComponent* StatsComponent)
{
	Activated = true;
	Timer = Time;
	StatsComponent->Slow(Amount);
}

void USlow::OnBuffTick(float DeltaTime)
{
	if(Timer > 0)
	{
		Timer -= DeltaTime;
	}else
	{
		Timer = 0;
	}
}

void USlow::OnBuffEnd(UStatsComponent* StatsComponent)
{
	StatsComponent->Slow(-Amount);
}