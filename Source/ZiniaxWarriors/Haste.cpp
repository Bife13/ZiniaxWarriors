// Fill out your copyright notice in the Description page of Project Settings.


#include "Haste.h"

void UHaste::OnBuffBegin(UStatsComponent* StatsComponent)
{
	Activated = true;
	Timer = Time;
	TemporarySpeed = StatsComponent->GetSpeed();
	StatsComponent->Haste(Amount);
	TemporarySpeedToSend = StatsComponent->GetSpeed() - TemporarySpeed;
}

void UHaste::OnBuffTick(float DeltaTime)
{
	if(Timer > 0)
	{
		Timer -= DeltaTime;
	}else
	{
		Timer = 0;
	}
}

void UHaste::OnBuffEnd(UStatsComponent* StatsComponent)
{
	StatsComponent->HasteRemove(TemporarySpeedToSend);
}
