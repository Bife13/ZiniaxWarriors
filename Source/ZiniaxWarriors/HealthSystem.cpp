// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthSystem.h"

#include "Net/UnrealNetwork.h"

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

void UHealthSystem::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(UHealthSystem, Health);
	DOREPLIFETIME(UHealthSystem, Shield);
}
#pragma endregion
#pragma region GeneralFunctions
void UHealthSystem::TakeDamage_Implementation(const float Amount)
{
	if (Amount > 0)
	{
		float damageTaken;
		float ExcedingDamage;
		if (Resistance > 0)
			damageTaken = Amount * ((100) / (100 + Resistance));
		else
			damageTaken = Amount * (2 - 100 / (100 - Resistance));

		if (Shield > 0)
		{
			Shield -= damageTaken;
			if (Shield < 0)
			{
				ExcedingDamage = Shield;
				Health -= ExcedingDamage;
				Shield = 0;
				HandleShieldBrokenEvent(ExcedingDamage);
				HandleDamageTakenEvent(ExcedingDamage);
			}
			else
			{
				HandleDamageTakenEvent(damageTaken);
			}
		}
		else
		{
			Health -= damageTaken;
			HandleDamageTakenEvent(damageTaken);
		}

		if (Health <= 0)
		{
			Health = 0;
			OnDeathEvent.Broadcast();
		}
	}
}

void UHealthSystem::HandleShieldBrokenEvent_Implementation(float Amount)
{
	OnShieldBrokenEvent.Broadcast(Amount);
}

void UHealthSystem::HandleDamageTakenEvent_Implementation(float Amount)
{
	MyOnDamageTakenEvent.Broadcast(Amount);
}

void UHealthSystem::RecoverHealth_Implementation(const float Amount)
{
	float HealAmount = Amount;
	if (HealAmount > 0 && Health != MaxHealth)
	{
		if (Health + HealAmount > MaxHealth)
		{
			HealAmount = MaxHealth - Health;
			Health = MaxHealth;
		}
		else
		{
			Health += HealAmount;
		}
		HandleHealEvent(HealAmount);
	}
}

void UHealthSystem::HandleHealEvent_Implementation(float Amount)
{
	OnDamageHealedEvent.Broadcast(Amount);
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

void UHealthSystem::SetShield_Implementation(float Amount)
{
	Shield = Amount;
}

void UHealthSystem::ResetHealth()
{
	Health = MaxHealth;
}

#pragma endregion
