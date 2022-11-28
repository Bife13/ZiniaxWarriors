// Fill out your copyright notice in the Description page of Project Settings.


#include "NyaxPassiveBase.h"

void UNyaxPassiveBase::OnHit()
{
	Super::OnHit();
	PassiveOwner->AddHaste(Time,Amount);
}
