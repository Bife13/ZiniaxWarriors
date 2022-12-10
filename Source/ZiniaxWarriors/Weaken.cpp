// Fill out your copyright notice in the Description page of Project Settings.


#include "Weaken.h"


void UWeaken::OnBuffBegin(UStatsComponent* StatsComponent)
{
	Activated = true;
	Timer = Time;
	StatsComponent->Weaken(Amount);
}

void UWeaken::OnBuffTick(float DeltaTime,TArray<IBuff*> CurrentBuffArray,TArray<IBuff*>* CurrentBuffArrayPointer,int index,UStatsComponent* StatComponent)
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

void UWeaken::OnBuffEnd(UStatsComponent* StatsComponent)
{
	StatsComponent->Weaken(-Amount);
}

float UWeaken::GetTimer()
{
	return Timer;
}
