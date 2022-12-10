// Fill out your copyright notice in the Description page of Project Settings.


#include "CastingSlow.h"

void UCastingSlow::OnBuffBegin(UStatsComponent* StatsComponent)
{
	Activated = true;
	Timer = Time;
	float const InitialSpeed = StatsComponent->GetSpeed();
	StatsComponent->CastingSlow(Amount);
	TemporarySpeed = InitialSpeed - StatsComponent->GetSpeed();
	
}

void UCastingSlow::OnBuffTick(float DeltaTime,TArray<IBuff*> CurrentBuffArray,TArray<IBuff*>* CurrentBuffArrayPointer,int index,UStatsComponent* StatComponent)
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

void UCastingSlow::OnBuffEnd(UStatsComponent* StatsComponent)
{
	StatsComponent->RemoveCastingSlow(TemporarySpeed);
}

float UCastingSlow::GetTimer()
{
	return Timer;
}

