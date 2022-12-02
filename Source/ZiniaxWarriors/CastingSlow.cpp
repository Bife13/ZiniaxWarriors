// Fill out your copyright notice in the Description page of Project Settings.


#include "CastingSlow.h"

void UCastingSlow::OnBuffBegin(UStatsComponent* StatsComponent)
{
	Activated = true;
	Timer = Time;
	float const initialSpeed = StatsComponent->GetSpeed();
	StatsComponent->CastingSlow(Amount);
	TemporarySpeed = initialSpeed - StatsComponent->GetSpeed();
	
}

void UCastingSlow::OnBuffTick(float DeltaTime)
{
	if(Timer > 0)
	{
		Timer -= DeltaTime;
	}else
	{
		Timer = 0;
	}
}

void UCastingSlow::OnBuffEnd(UStatsComponent* StatsComponent)
{
	StatsComponent->RemoveCastingSlow(TemporarySpeed);
}