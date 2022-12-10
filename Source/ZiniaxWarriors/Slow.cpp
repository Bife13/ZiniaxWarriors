// Fill out your copyright notice in the Description page of Project Settings.


#include "Slow.h"

void USlow::OnBuffBegin(UStatsComponent* StatsComponent)
{
	Activated = true;
	Timer = Time;
	float const initialSpeed = StatsComponent->GetSpeed();
	StatsComponent->Slow(Amount);
	TemporarySpeed = initialSpeed - StatsComponent->GetSpeed();
}

void USlow::OnBuffTick(float DeltaTime,TArray<IBuff*> CurrentBuffArray,TArray<IBuff*>* CurrentBuffArrayPointer,int index,UStatsComponent* StatComponent)
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

void USlow::OnBuffEnd(UStatsComponent* StatsComponent)
{
	StatsComponent->SlowRemove(TemporarySpeed);
}

float USlow::GetTimer()
{
	return Timer;
}
