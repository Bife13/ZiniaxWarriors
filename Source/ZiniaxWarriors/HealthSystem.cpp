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
		float DamageTaken;
		float ExcedingDamage;
		if (Resistance > 0)
			DamageTaken = Amount * ((100) / (100 + Resistance));
		else
			DamageTaken = Amount * (2 - 100 / (100 - Resistance));

		if (Shield > 0)
		{
			Shield -= DamageTaken;
			if (Shield < 0)
			{
				ExcedingDamage = Shield;
				Health -= ExcedingDamage;
				Shield = 0;
				HandleShieldBrokenEvent(ExcedingDamage);
				HandleHealthChanged(GetHealth(),GetMaxHealth(),GetHealthAsPercentage(),ExcedingDamage);
			}
			else
			{
				HandleHealthChanged(GetHealth(),GetMaxHealth(),GetHealthAsPercentage(),DamageTaken);
			}
		}
		else
		{
			Health -= DamageTaken;
			HandleHealthChanged(GetHealth(),GetMaxHealth(),GetHealthAsPercentage(),DamageTaken);
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

void UHealthSystem::HandleHealthChanged_Implementation(float CurrentH, float MaxH,float GetHAsPercentage, float DamageTaken)
{
	OnHealthDecreased.Broadcast(CurrentH, MaxH, GetHAsPercentage,DamageTaken);
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
		HandleHealEvent(GetHealth(),GetMaxHealth(),GetHealthAsPercentage(),HealAmount);
	}
}

void UHealthSystem::HandleHealEvent_Implementation(float CurrentH, float MaxH,float GetHAsPercentage, float HealingValue)
{
	OnHealEvent.Broadcast(CurrentH, MaxH, GetHAsPercentage,HealingValue);
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
	HandleHealthChanged(GetHealth(),GetMaxHealth(),GetHealthAsPercentage(),0);
}

void UHealthSystem::SetMaxHealth(float Amount)
{
	MaxHealth = Amount;
	HandleHealthChanged(GetHealth(),GetMaxHealth(),GetHealthAsPercentage(),0);

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
	HandleHealthChanged(GetHealth(),GetMaxHealth(),GetHealthAsPercentage(),0);
}

#pragma endregion
