// Fill out your copyright notice in the Description page of Project Settings.


#include "StatusEffectsComponent.h"

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


UStatusEffectsComponent::UStatusEffectsComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


void UStatusEffectsComponent::SetStatsComponent(UStatsComponent* StatsComponentToSet)
{
	StatsComponent = StatsComponentToSet;
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


	if (CurrentBuffArray.Num() > 0 && CurrentBuffInterface.Num() > 0)
	{
		for (int i = 0; i < CurrentBuffArray.Num(); i++)
		{
			if (CurrentBuffArray.IsValidIndex(i) && CurrentBuffInterface.IsValidIndex(i))
			{
				// Cast<IBuff>(CurrentBuffArray[i])->OnBuffTick(DeltaTime);
				CurrentBuffInterface[i]->OnBuffTick(DeltaTime);

				if (CurrentBuffInterface[i]->GetTimer() == 0)
				{
					CurrentBuffInterface[i]->OnBuffEnd(StatsComponent);
					CurrentBuffArray.RemoveAt(i);
					CurrentBuffInterface.RemoveAt(i);
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
	CurrentBuffInterface.Add(Cast<IBuff>(BuffToAdd));
}

void UStatusEffectsComponent::AddBulk(float TimeAmount, float BuffAmount)
{
	UObject* BuffToAdd = BuffFactory->CreateBuff<UBulk>(TimeAmount, BuffAmount, StatsComponent);
	CurrentBuffArray.Add(BuffToAdd);
	CurrentBuffInterface.Add(Cast<IBuff>(BuffToAdd));
}

void UStatusEffectsComponent::AddHaste(float TimeAmount, float BuffAmount)
{
	UObject* BuffToAdd = BuffFactory->CreateBuff<UHaste>(TimeAmount, BuffAmount, StatsComponent);
	CurrentBuffArray.Add(BuffToAdd);
	CurrentBuffInterface.Add(Cast<IBuff>(BuffToAdd));
}

void UStatusEffectsComponent::AddSlow(float TimeAmount, float DebuffAmount)
{
	UObject* BuffToAdd = BuffFactory->CreateBuff<USlow>(TimeAmount, DebuffAmount, StatsComponent);
	CurrentBuffArray.Add(BuffToAdd);
	CurrentBuffInterface.Add(Cast<IBuff>(BuffToAdd));
}

void UStatusEffectsComponent::AddWeaken(float TimeAmount, float DebuffAmount)
{
	UObject* BuffToAdd = BuffFactory->CreateBuff<UWeaken>(TimeAmount, DebuffAmount, StatsComponent);
	CurrentBuffArray.Add(BuffToAdd);
	CurrentBuffInterface.Add(Cast<IBuff>(BuffToAdd));
}

void UStatusEffectsComponent::AddVulnerable(float TimeAmount, float DebuffAmount)
{
	UObject* BuffToAdd = BuffFactory->CreateBuff<UVulnerable>(TimeAmount, DebuffAmount, StatsComponent);
	CurrentBuffArray.Add(BuffToAdd);
	CurrentBuffInterface.Add(Cast<IBuff>(BuffToAdd));
}

void UStatusEffectsComponent::AddRoot(float TimeAmount)
{
	UObject* BuffToAdd = BuffFactory->CreateBuff<URoot>(TimeAmount, TimeAmount, StatsComponent);
	CurrentBuffArray.Add(BuffToAdd);
	CurrentBuffInterface.Add(Cast<IBuff>(BuffToAdd));
}

void UStatusEffectsComponent::AddShield(float TimeAmount, float BuffAmount)
{
	UObject* BuffToAdd = BuffFactory->CreateBuff<UShield>(TimeAmount, BuffAmount, StatsComponent);
	CurrentBuffArray.Add(BuffToAdd);
	CurrentBuffInterface.Add(Cast<IBuff>(BuffToAdd));
}

void UStatusEffectsComponent::AddCastingSlow(float TimeAmount, float BuffAmount)
{
	UObject* BuffToAdd = BuffFactory->CreateBuff<UCastingSlow>(TimeAmount, BuffAmount, StatsComponent);
	CurrentBuffArray.Add(BuffToAdd);
	CurrentBuffInterface.Add(Cast<IBuff>(BuffToAdd));
}
