// Fill out your copyright notice in the Description page of Project Settings.


#include "Shield.h"

void UShield::OnBuffBegin(UStatsComponent* StatsComponent)
{
	Activated = true;
	Timer = Time;
	StatsComponent->Shield(Amount);
}

void UShield::OnBuffTick(float DeltaTime)
{
	if(Timer > 0)
	{
		Timer -= DeltaTime;
	}else
	{
		Timer = 0;
	}
}

void UShield::OnBuffEnd(UStatsComponent* StatsComponent)
{
	StatsComponent->RemoveShield(Amount);
}