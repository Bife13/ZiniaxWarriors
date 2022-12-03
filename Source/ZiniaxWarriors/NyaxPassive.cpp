// Fill out your copyright notice in the Description page of Project Settings.


#include "NyaxPassive.h"

void UNyaxPassive::OnHit()
{
	Super::OnHit();
	PassiveOwner->AddHaste(Time,Amount);
}
