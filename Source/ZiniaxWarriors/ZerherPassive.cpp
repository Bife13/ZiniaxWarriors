// Fill out your copyright notice in the Description page of Project Settings.


#include "ZerherPassive.h"

void UZerherPassive::OnTick(float DeltaTime)
{
	if(Timer > 0)
	{
		Timer -= DeltaTime;
		GEngine->AddOnScreenDebugMessage(1,2,FColor::Blue,FString::Printf(TEXT("%f"),Timer));

	}
	else
	{
		PassiveOwner->AddShield(Cooldown - 2,ShieldForce);
		GEngine->AddOnScreenDebugMessage(1,2,FColor::Blue,"SHIELD");
		Timer = Cooldown;
	}
}
