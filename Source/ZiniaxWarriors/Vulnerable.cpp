// Fill out your copyright notice in the Description page of Project Settings.


#include "Vulnerable.h"

void UVulnerable::OnBuffBegin(UStatsComponent* StatsComponent)
{
	Activated = true;
	Timer = Time;
	StatsComponent->Vulnerable(Amount);
}

void UVulnerable::OnBuffTick(float DeltaTime)
{
	if(Timer > 0)
	{
		Timer -= DeltaTime;
	}else
	{
		Timer = 0;
	}
}
void UVulnerable::OnBuffEnd(UStatsComponent* StatsComponent)
{
	StatsComponent->Vulnerable(-Amount);
}

float UVulnerable::GetTimer()
{
	return Timer;
}
