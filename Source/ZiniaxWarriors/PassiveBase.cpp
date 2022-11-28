// Fill out your copyright notice in the Description page of Project Settings.


#include "PassiveBase.h"

void UPassiveBase::OnHit()
{
}

void UPassiveBase::InitializePassive(IBuffable* OwnerCharacter)
{
	PassiveOwner = OwnerCharacter;
}
