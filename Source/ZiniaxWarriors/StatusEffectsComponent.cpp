// Fill out your copyright notice in the Description page of Project Settings.


#include "StatusEffectsComponent.h"

#include <array>

#include "FBuffFactory.h"
#include "Enrage.h"
#include "Bulk.h"
#include "CastingSlow.h"
#include "Haste.h"
#include "Root.h"
#include "Shield.h"
#include "Slow.h"
#include "Vulnerable.h"
#include "Weaken.h"
#include "Net/UnrealNetwork.h"


UStatusEffectsComponent::UStatusEffectsComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

void UStatusEffectsComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(UStatusEffectsComponent, CurrentBuffArray);
	DOREPLIFETIME(UStatusEffectsComponent, ArrayLength);
}


void UStatusEffectsComponent::SetStatsComponent(UStatsComponent* StatsComponentToSet)
{
	StatsComponent = StatsComponentToSet;
}

void UStatusEffectsComponent::CleanBuffs()
{
	if (CurrentBuffArray.Num() > 0 && CurrentBuffInterfaceArray.Num() > 0)
	{
		for (int i = CurrentBuffArray.Num() - 1; i >= 0; i--)
		{
			if (CurrentBuffArray.IsValidIndex(i) && CurrentBuffInterfaceArray.IsValidIndex(i))
			{
				CurrentBuffInterfaceArray[i]->OnBuffEnd(StatsComponent);
				CurrentBuffArray.RemoveAt(i);
				CurrentBuffInterfaceArray.RemoveAt(i);
			}
		}
	}
}

void UStatusEffectsComponent::BeginPlay()
{
	Super::BeginPlay();

	BuffFactory = new FBuffFactory();
	// CurrentBuffArray.Empty();
}

void UStatusEffectsComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                            FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	TickArrays(DeltaTime);
}

void UStatusEffectsComponent::TickArrays(float DeltaTime)
{
	if (CurrentBuffArray.Num() > 0 && CurrentBuffInterfaceArray.Num() > 0)
	{
		for (int i = CurrentBuffArray.Num() - 1; i >= 0; i--)
		{
			if (CurrentBuffArray.IsValidIndex(i) && CurrentBuffInterfaceArray.IsValidIndex(i))
			{
				CurrentBuffInterfaceArray[i]->OnBuffTick(DeltaTime);

				if (CurrentBuffInterfaceArray[i]->GetTimer() == 0)
				{
					CurrentBuffInterfaceArray[i]->OnBuffEnd(StatsComponent);
					CurrentBuffArray.RemoveAt(i);
					CurrentBuffInterfaceArray.RemoveAt(i);
				}
			}
			else
			{
				break;
			}
		}
	}

	ArrayLength = CurrentBuffArray.Num();
}

void UStatusEffectsComponent::AddEnrage(float TimeAmount, float BuffAmount)
{
	UObject* BuffToAdd = BuffFactory->CreateBuff<UEnrage>(TimeAmount, BuffAmount, StatsComponent);
	CurrentBuffArray.Add(BuffToAdd);
	CurrentBuffInterfaceArray.Add(Cast<IBuff>(BuffToAdd));
}

void UStatusEffectsComponent::AddBulk(float TimeAmount, float BuffAmount)
{
	UObject* BuffToAdd = BuffFactory->CreateBuff<UBulk>(TimeAmount, BuffAmount, StatsComponent);
	CurrentBuffArray.Add(BuffToAdd);
	CurrentBuffInterfaceArray.Add(Cast<IBuff>(BuffToAdd));
}

void UStatusEffectsComponent::AddHaste(float TimeAmount, float BuffAmount)
{
	UObject* BuffToAdd = BuffFactory->CreateBuff<UHaste>(TimeAmount, BuffAmount, StatsComponent);
	CurrentBuffArray.Add(BuffToAdd);
	CurrentBuffInterfaceArray.Add(Cast<IBuff>(BuffToAdd));
}

void UStatusEffectsComponent::AddSlow(float TimeAmount, float DebuffAmount)
{
	UObject* BuffToAdd = BuffFactory->CreateBuff<USlow>(TimeAmount, DebuffAmount, StatsComponent);
	CurrentBuffArray.Add(BuffToAdd);
	CurrentBuffInterfaceArray.Add(Cast<IBuff>(BuffToAdd));
}

void UStatusEffectsComponent::AddWeaken(float TimeAmount, float DebuffAmount)
{
	UObject* BuffToAdd = BuffFactory->CreateBuff<UWeaken>(TimeAmount, DebuffAmount, StatsComponent);
	CurrentBuffArray.Add(BuffToAdd);
	CurrentBuffInterfaceArray.Add(Cast<IBuff>(BuffToAdd));
}

void UStatusEffectsComponent::AddVulnerable(float TimeAmount, float DebuffAmount)
{
	UObject* BuffToAdd = BuffFactory->CreateBuff<UVulnerable>(TimeAmount, DebuffAmount, StatsComponent);
	CurrentBuffArray.Add(BuffToAdd);
	CurrentBuffInterfaceArray.Add(Cast<IBuff>(BuffToAdd));
}

void UStatusEffectsComponent::AddRoot(float TimeAmount)
{
	UObject* BuffToAdd = BuffFactory->CreateBuff<URoot>(TimeAmount, TimeAmount, StatsComponent);
	CurrentBuffArray.Add(BuffToAdd);
	CurrentBuffInterfaceArray.Add(Cast<IBuff>(BuffToAdd));
}

void UStatusEffectsComponent::AddShield(float TimeAmount, float BuffAmount)
{
	UObject* BuffToAdd = BuffFactory->CreateBuff<UShield>(TimeAmount, BuffAmount, StatsComponent);
	CurrentBuffArray.Add(BuffToAdd);
	CurrentBuffInterfaceArray.Add(Cast<IBuff>(BuffToAdd));
}

void UStatusEffectsComponent::AddCastingSlow(float TimeAmount, float BuffAmount)
{
	UObject* BuffToAdd = BuffFactory->CreateBuff<UCastingSlow>(TimeAmount, BuffAmount, StatsComponent);
	CurrentBuffArray.Add(BuffToAdd);
	CurrentBuffInterfaceArray.Add(Cast<IBuff>(BuffToAdd));
}
