// Fill out your copyright notice in the Description page of Project Settings.


#include "ZerherPassive.h"

#include "Net/UnrealNetwork.h"

void UZerherPassive::OnTick_Implementation(float DeltaTime)
{
	if(Timer > 0)
	{
		Timer -= DeltaTime;
	}
	else
	{	

		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("GOT HERE")));
		PassiveOwner->AddShieldPassive(Cooldown / 3,ShieldForce);

		Timer = Cooldown;
	}
}

void UZerherPassive::OnHit()
{
	Super::OnHit();	
}

float UZerherPassive::CheckDistance(float Damage, APawn* Owner, APawn* Target)
{
	return Super::CheckDistance(Damage, Owner, Target);
}

void UZerherPassive::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(UZerherPassive, Timer );
	DOREPLIFETIME(UZerherPassive, Cooldown);
}
