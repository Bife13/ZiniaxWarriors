// Fill out your copyright notice in the Description page of Project Settings.


#include "PowerBuff.h"


void UPowerBuff::OnBuffBegin(UStatsComponent* StatsComponent)
{
	Activated = true;
	Timer = Time;
	StatsComponent->ChangePower(Amount);
	GEngine->AddOnScreenDebugMessage(1,1,FColor::Black,"BuffGained");
}

void UPowerBuff::OnBuffTick(float DeltaTime)
{
	if(Timer > 0)
	{
		Timer -= DeltaTime;
	}else
	{
		Timer = 0;
	}
}

void UPowerBuff::OnBuffEnd(UStatsComponent* StatsComponent)
{
	StatsComponent->ChangePower(-Amount);
	GEngine->AddOnScreenDebugMessage(1,1,FColor::Black,"BuffLost");

}
