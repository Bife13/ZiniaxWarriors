// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthSystem.h"

#pragma region MustHaveFunctions
UHealthSystem::UHealthSystem()
{
	// This is a component that doesn't need a tick so lets disable it
	PrimaryComponentTick.bCanEverTick = false;
	PrimaryComponentTick.bStartWithTickEnabled = false;
}

void UHealthSystem::BeginPlay()
{
	Super::BeginPlay();
	Health = MaxHealth;
}
#pragma endregion
#pragma region GeneralFunctions
void UHealthSystem::TakeDamage(const float Amount)
{
	if (Amount > 0)
	{
	float damageTaken; float ExcedingDamage; 
	     if(Resistance > 0)
		 damageTaken = Amount * ((100) / (100 + Resistance));
		 else
		 damageTaken = Amount * ( 2 - 100 / (100 - Resistance));
		if(Shield > 0)
		{
			Shield -= damageTaken;
			if(Shield < 0)
			{
				ExcedingDamage = Shield;
				Health -= ExcedingDamage;
				Shield = 0;
			}
			MyOnDamageTakenEvent.Broadcast(damageTaken);
		}
		else
		{
			Health -= damageTaken;
			MyOnDamageTakenEvent.Broadcast(damageTaken);
		}
	}
}

void UHealthSystem::RecoverHealth(const float Amount)
{
	if (Amount > 0)
	{
		if(Health+ Amount>MaxHealth)
		{
			Health = MaxHealth;
		}
		else
		{
			Health += Amount;
		}
		
		OnDamageHealedEvent.Broadcast(Amount);
	}
}
#pragma endregion
#pragma region Gets
float UHealthSystem::GetHealth() const
{
	return Health;
}

float UHealthSystem::GetMaxHealth() const
{
	return MaxHealth;
}

float UHealthSystem::GetHealthAsPercentage() const
{
	return Health / MaxHealth;
}
#pragma endregion
#pragma region Sets
void UHealthSystem::SetHealthToMaxHealth()
{
	Health = MaxHealth;
}

void UHealthSystem::SetMaxHealth(float Amount)
{
	MaxHealth = Amount;
}

void UHealthSystem::SetResistance(float Amount)
{
	if (Amount != NULL)
	{
		Resistance = Amount;
	}
}

void UHealthSystem::SetShield(float Amount)
{
	Shield = Amount;
}

#pragma endregion
