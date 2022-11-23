// Fill out your copyright notice in the Description page of Project Settings.


#include "ResistanceBuff.h"

void UResistanceBuff::OnBuffBegin(UStatsComponent* StatsComponent)
{
	Activated = true;
	Timer = Time;
}

void UResistanceBuff::OnBuffTick()
{
}

void UResistanceBuff::OnBuffEnd(UStatsComponent* StatsComponent)
{
}
