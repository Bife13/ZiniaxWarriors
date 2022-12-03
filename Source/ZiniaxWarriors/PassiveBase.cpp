// Fill out your copyright notice in the Description page of Project Settings.


#include "PassiveBase.h"


void UPassiveBase::OnHit()
{
	
}

float UPassiveBase::CheckDistance(float Damage, APawn* Owner, APawn* target)
{
	return Damage;
}

void UPassiveBase::InitializePassive(IBuffable* OwnerCharacter)
{
	PassiveOwner = OwnerCharacter;
}

void UPassiveBase::OnTick(float DeltaTime)
{
}
