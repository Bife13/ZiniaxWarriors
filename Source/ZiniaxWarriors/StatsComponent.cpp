// Fill out your copyright notice in the Description page of Project Settings.


#include "StatsComponent.h"

// Sets default values for this component's properties
UStatsComponent::UStatsComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


void UStatsComponent::SetupStatSystem(float PowerValue, float SpeedValue, float MaximumHealthValue,
                                      float ResistanceValue,
                                      float ViewRangeValue)
{
	BaseSpeed = SpeedValue;
	BasePower = PowerValue;
	BaseMaximumHealth=MaximumHealthValue;
	BaseResistance=ResistanceValue;
	BaseViewRange=ViewRangeValue;

	CurrentSpeed = BaseSpeed;
	CurrentPower = BasePower;
	CurrentMaximumHealth = BaseMaximumHealth;
	CurrentResistance = BaseResistance;
	CurrentViewRange = BaseViewRange;
}


// Called when the game starts
void UStatsComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
}


// Called every frame
void UStatsComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UStatsComponent::Enrage(float Amount)
{
	CurrentPower += (BasePower * Amount);
	if(Amount > 0)
	{
		OnEnrageAppliedEvent.Broadcast(CurrentPower);		
	}
	else
	{
		OnEnrageRemovedEvent.Broadcast(CurrentPower);
	}
}

void UStatsComponent::Weaken(float Amount)
{
	CurrentPower -= (BasePower * Amount);
	if(Amount > 0)
	{
		OnWeakenAppliedEvent.Broadcast(CurrentPower);		
	}
	else
	{
		OnWeakenRemovedEvent.Broadcast(CurrentPower);
	}
}

void UStatsComponent::Bulk(float Amount)
{
	CurrentResistance += (BaseResistance * Amount);
	if(Amount > 0)
	{
		OnBulkAppliedEvent.Broadcast(CurrentResistance);		
	}
	else
	{
		OnBulkRemovedEvent.Broadcast(CurrentResistance);
	}
}

void UStatsComponent::Vulnerable(float Amount)
{
	CurrentResistance -= (BaseResistance * Amount);
	if(Amount > 0)
	{
		OnVulnerableAppliedEvent.Broadcast(CurrentResistance);		
	}
	else
	{
		OnVulnerableRemovedEvent.Broadcast(CurrentResistance);
	}
}

void UStatsComponent::Haste(float Amount)
{
	CurrentSpeed += (CurrentSpeed * Amount);
	OnHasteAppliedEvent.Broadcast(CurrentSpeed);		

}

void UStatsComponent::HasteRemove(float Amount)
{
	CurrentSpeed -= Amount;
	OnHasteRemovedEvent.Broadcast(CurrentSpeed);
}

void UStatsComponent::Slow(float Amount)
{
	CurrentSpeed -= (CurrentSpeed * Amount);
	OnSlowAppliedEvent.Broadcast(CurrentSpeed);
}

void UStatsComponent::SlowRemove(float Amount)
{
	CurrentSpeed += Amount;
	OnSlowRemovedEvent.Broadcast(CurrentSpeed);
}

void UStatsComponent::Root()
{
	CurrentSpeed -= CurrentSpeed + 0;
	OnRootApplied.Broadcast();
}

void UStatsComponent::EndRoot(float Amount)
{
	CurrentSpeed = Amount;
	OnRootRemoved.Broadcast();
}






