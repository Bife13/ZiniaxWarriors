// Fill out your copyright notice in the Description page of Project Settings.


#include "DrexPassive.h"

float UDrexPassive::CheckDistance(float Damage, APawn* Owner, APawn* Target)
{
	
	
	FVector const OwnerLocation = Owner->GetActorLocation();
	FVector const TargetLocation = Target->GetActorLocation();

	float const Distance = FVector::Distance(OwnerLocation,TargetLocation);
	if(Distance > TolerationDistance)
	{
		Damage -= (Damage * DamageChange);
	}
	else
	{
		Damage += (Damage * DamageChange);
	}

	return Damage;

	
}

void UDrexPassive::OnTick(float DeltaTime)
{
	Super::OnTick(DeltaTime);
}

void UDrexPassive::OnHit()
{
	Super::OnHit();
}
