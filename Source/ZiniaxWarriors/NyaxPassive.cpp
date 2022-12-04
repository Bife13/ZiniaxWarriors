// Fill out your copyright notice in the Description page of Project Settings.


#include "NyaxPassive.h"

void UNyaxPassive::OnHit()
{
	Super::OnHit();
	PassiveOwner->AddHastePassive(Time,Amount);
}

float UNyaxPassive::CheckDistance(float Damage, APawn* Owner, APawn* Target)
{
	return Super::CheckDistance(Damage, Owner, Target);
}

void UNyaxPassive::OnTick(float DeltaTime)
{
	Super::OnTick(DeltaTime);
}
 