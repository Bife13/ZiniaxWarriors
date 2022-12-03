// Fill out your copyright notice in the Description page of Project Settings.


#include "ZerherPassive.h"

void UZerherPassive::OnTick(float DeltaTime)
{
	if(Timer < Cooldown)
	{
		Timer += DeltaTime;
	}
	else
	{
		PassiveOwner->AddShield(Cooldown - 2,ShieldForce);
		Timer = 0;
	}
}
