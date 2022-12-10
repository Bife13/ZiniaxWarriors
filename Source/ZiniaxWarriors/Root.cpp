// Fill out your copyright notice in the Description page of Project Settings.


#include "Root.h"


void URoot::OnBuffBegin(UStatsComponent* StatsComponent)
{
	Activated = true;
	Timer = Time;
	TemporarySpeed = StatsComponent->GetSpeed();
	StatsComponent->Root();
}

void URoot::OnBuffTick(float DeltaTime)
{
	if(Timer > 0)
	{
		Timer -= DeltaTime;
	}else
	{
		Timer = 0;
	}
}

void URoot::OnBuffEnd(UStatsComponent* StatsComponent)
{
	StatsComponent->EndRoot(TemporarySpeed);
}

float URoot::GetTimer()
{
	return Timer;
}
