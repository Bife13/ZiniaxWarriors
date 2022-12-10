// Fill out your copyright notice in the Description page of Project Settings.


#include "Enrage.h"


void UEnrage::OnBuffBegin(UStatsComponent* StatsComponent)
{
	Activated = true;
	Timer = Time;
	StatsComponent->Enrage(Amount);
}

void UEnrage::OnBuffTick(float DeltaTime)
{
	if(Timer > 0)
	{
		Timer -= DeltaTime;
	}else
	{
		Timer = 0;
	}
}
void UEnrage::OnBuffEnd(UStatsComponent* StatsComponent)
{
	StatsComponent->Enrage(-Amount);
}

float UEnrage::GetTimer()
{
	return Timer;
}
