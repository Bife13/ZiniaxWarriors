// Fill out your copyright notice in the Description page of Project Settings.


#include "Bulk.h"

void UBulk::OnBuffBegin(UStatsComponent* StatsComponent)
{
	Activated = true;
	Timer = Time;
	StatsComponent->Bulk(Amount);
}

void UBulk::OnBuffTick(float DeltaTime,TArray<IBuff*> CurrentBuffArray,TArray<IBuff*>* CurrentBuffArrayPointer,int index,UStatsComponent* StatComponent)
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

void UBulk::OnBuffEnd(UStatsComponent* StatsComponent)
{
	StatsComponent->Bulk(-Amount);
}

float UBulk::GetTimer()
{
	return Timer;
}
