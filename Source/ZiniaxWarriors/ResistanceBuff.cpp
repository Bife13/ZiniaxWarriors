// Fill out your copyright notice in the Description page of Project Settings.


#include "ResistanceBuff.h"

void UResistanceBuff::OnBuffBegin()
{
	GEngine->AddOnScreenDebugMessage(1, 2, FColor::White, FString::Printf(TEXT("%f"), Time));
	Activated = true;
	Timer = Time;
}

void UResistanceBuff::OnBuffTick()
{
}

void UResistanceBuff::OnBuffEnd()
{
	GEngine->AddOnScreenDebugMessage(1, 2, FColor::White, "CARALHO");
}
