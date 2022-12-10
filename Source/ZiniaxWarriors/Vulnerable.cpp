// Fill out your copyright notice in the Description page of Project Settings.


#include "Vulnerable.h"

void UVulnerable::OnBuffBegin(UStatsComponent* StatsComponent)
{
	Activated = true;
	Timer = Time;
	StatsComponent->Vulnerable(Amount);
}

void UVulnerable::OnBuffTick(float DeltaTime,TArray<IBuff*> CurrentBuffArray,TArray<IBuff*>* CurrentBuffArrayPointer,int index,UStatsComponent* StatComponent)
{
	if(Timer > 0)
	{
		Timer -= DeltaTime;
	}else
	{
		
		CurrentBuffArray[index]->OnBuffEnd(StatComponent);
		CurrentBuffArrayPointer->RemoveAt(index, 1, true);
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
