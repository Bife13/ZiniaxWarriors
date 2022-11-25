// Fill out your copyright notice in the Description page of Project Settings.


#include "StatusEffectsComponent.h"

#include "FBuffFactory.h"
#include "Enrage.h"
#include "Bulk.h"
#include "Haste.h"
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
}

void UStatusEffectsComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                            FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (CurrentBuffArray.Num() > 0)
	{
		for (int i = 0; i < CurrentBuffArray.Num(); ++i)
		{
			if (CurrentBuffArray[i])
			{
				if (!CurrentBuffArray[i]->GetActivated())
				{
					CurrentBuffArray[i]->OnBuffBegin(StatsComponent);
				}
				
				CurrentBuffArray[i]->OnBuffTick(DeltaTime);

				if (CurrentBuffArray[i]->GetTimer() <= 0)
				{
					CurrentBuffArray[i]->OnBuffEnd(StatsComponent);
					CurrentBuffArray.RemoveAt(i,1,true);
				}
			}
		}
	}

	ArrayLength = CurrentBuffArray.Num();
}

<<<<<<< HEAD
void UStatusEffectsComponent::AddPowerBuff(float TimeAmount, float BuffAmount)
{
	CurrentBuffArray.Add(BuffFactory->CreateBuff<UPowerBuff>(TimeAmount, BuffAmount));
	
}

void UStatusEffectsComponent::AddResistanceBuff(float TimeAmount, float BuffAmount)
{
	CurrentBuffArray.Add(BuffFactory->CreateBuff<UResistanceBuff>(TimeAmount, BuffAmount));
}

=======
void UStatusEffectsComponent::AddEnrage(float TimeAmount, float BuffAmount)
{
	CurrentBuffArray.Add(BuffFactory->CreateBuff<UEnrage>(TimeAmount, BuffAmount));
	
}

void UStatusEffectsComponent::AddBulk(float TimeAmount, float BuffAmount)
{
	CurrentBuffArray.Add(BuffFactory->CreateBuff<UBulk>(TimeAmount, BuffAmount));
}

void UStatusEffectsComponent::AddHaste(float TimeAmount, float BuffAmount)
{
	CurrentBuffArray.Add(BuffFactory->CreateBuff<UHaste>(TimeAmount,BuffAmount));
}

void UStatusEffectsComponent::AddSlow(float TimeAmount, float DebuffAmount)
{
	CurrentBuffArray.Add(BuffFactory->CreateBuff<USlow>(TimeAmount,DebuffAmount));
}

void UStatusEffectsComponent::AddWeaken(float TimeAmount, float DebuffAmount)
{
	CurrentBuffArray.Add(BuffFactory->CreateBuff<UWeaken>(TimeAmount,DebuffAmount));
}

void UStatusEffectsComponent::AddVulnerable(float TimeAmount, float DebuffAmount)
{
	CurrentBuffArray.Add(BuffFactory->CreateBuff<UVulnerable>(TimeAmount,DebuffAmount));
}



>>>>>>> master-bife
