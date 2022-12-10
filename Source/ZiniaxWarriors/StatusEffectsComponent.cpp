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
	CurrentBuffArray.Empty();
	PointerCurrentArray = &CurrentBuffArray;
}

void UStatusEffectsComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                            FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);


	if (CurrentBuffArray.Num() > 0)
	{
		for(int i = 0; i < CurrentBuffArray.Num(); i++)
		{
			if(CurrentBuffArray.IsValidIndex(i))
			{
				CurrentBuffArray[i]->OnBuffTick(DeltaTime,CurrentBuffArray,PointerCurrentArray,i,StatsComponent);		
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
	CurrentBuffArray.Add(BuffFactory->CreateBuff<UEnrage>(TimeAmount, BuffAmount,StatsComponent));
}

void UStatusEffectsComponent::AddBulk(float TimeAmount, float BuffAmount)
{
	CurrentBuffArray.Add(BuffFactory->CreateBuff<UBulk>(TimeAmount, BuffAmount,StatsComponent));
}

void UStatusEffectsComponent::AddHaste(float TimeAmount, float BuffAmount)
{
	CurrentBuffArray.Add(BuffFactory->CreateBuff<UHaste>(TimeAmount, BuffAmount,StatsComponent));
}

void UStatusEffectsComponent::AddSlow(float TimeAmount, float DebuffAmount)
{
	CurrentBuffArray.Add(BuffFactory->CreateBuff<USlow>(TimeAmount, DebuffAmount,StatsComponent));
}

void UStatusEffectsComponent::AddWeaken(float TimeAmount, float DebuffAmount)
{
	CurrentBuffArray.Add(BuffFactory->CreateBuff<UWeaken>(TimeAmount, DebuffAmount,StatsComponent));
}

void UStatusEffectsComponent::AddVulnerable(float TimeAmount, float DebuffAmount)
{
	CurrentBuffArray.Add(BuffFactory->CreateBuff<UVulnerable>(TimeAmount, DebuffAmount,StatsComponent));
}

void UStatusEffectsComponent::AddRoot(float TimeAmount)
{
	CurrentBuffArray.Add(BuffFactory->CreateBuff<URoot>(TimeAmount, 0,StatsComponent));
}

void UStatusEffectsComponent::AddShield(float TimeAmount, float BuffAmount)
{
	CurrentBuffArray.Add(BuffFactory->CreateBuff<UShield>(TimeAmount, BuffAmount,StatsComponent));
}

void UStatusEffectsComponent::AddCastingSlow(float TimeAmount, float BuffAmount)
{
	CurrentBuffArray.Add(BuffFactory->CreateBuff<UCastingSlow>(TimeAmount, BuffAmount,StatsComponent));
}
