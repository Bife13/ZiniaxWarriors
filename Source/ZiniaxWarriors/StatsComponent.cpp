// Fill out your copyright notice in the Description page of Project Settings.


#include "StatsComponent.h"

// Sets default values for this component's properties
UStatsComponent::UStatsComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


void UStatsComponent::CastingSlow(float Amount)
{
	CurrentSpeed -= (CurrentSpeed * Amount);
	OnCastingSlowApplied.Broadcast(Amount);
}

void UStatsComponent::RemoveCastingSlow(float Amount)
{
	CurrentSpeed += Amount;
	OnCastingSlowRemovedEvent.Broadcast(Amount);
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
		BuffApllied.Broadcast("ENRAGE",true,1);
	}
	else
	{
		OnEnrageRemovedEvent.Broadcast(CurrentPower);
		BuffRemove.Broadcast("ENRAGE",true,1);
	}
}

void UStatsComponent::Weaken(float Amount)
{
	CurrentPower -= (BasePower * Amount);
	if(Amount > 0)
	{
		OnWeakenAppliedEvent.Broadcast(CurrentPower);
		BuffApllied.Broadcast("WEAKEN",false,1);
	}
	else
	{
		OnWeakenRemovedEvent.Broadcast(CurrentPower);
		BuffRemove.Broadcast("WEAKEN",false,1);
	}
}

void UStatsComponent::Bulk(float Amount)
{
	CurrentResistance += (BaseResistance * Amount);
	if(Amount > 0)
	{
		OnBulkAppliedEvent.Broadcast(CurrentResistance);
		BuffApllied.Broadcast("BULK",true,2);
	}
	else
	{
		OnBulkRemovedEvent.Broadcast(CurrentResistance);
		BuffRemove.Broadcast("BULK",true,2);
	}
}

void UStatsComponent::Vulnerable(float Amount)
{
	CurrentResistance -= (BaseResistance * Amount);
	if(Amount > 0)
	{
		OnVulnerableAppliedEvent.Broadcast(CurrentResistance);
		BuffApllied.Broadcast("VULNERABLE",false,2);
	}
	else
	{
		OnVulnerableRemovedEvent.Broadcast(CurrentResistance);
		BuffRemove.Broadcast("VULNERABLE",false,2);
	}

}

void UStatsComponent::Haste(float Amount)
{
	CurrentSpeed += (CurrentSpeed * Amount);
	OnHasteAppliedEvent.Broadcast(CurrentSpeed);		
	BuffApllied.Broadcast("HASTE",true,3);
}

void UStatsComponent::HasteRemove(float Amount)
{
	CurrentSpeed -= Amount;
	OnHasteRemovedEvent.Broadcast(CurrentSpeed);
	BuffRemove.Broadcast("HASTE",true,3);
}

void UStatsComponent::Slow(float Amount)
{
	CurrentSpeed -= (CurrentSpeed * Amount);
	OnSlowAppliedEvent.Broadcast(CurrentSpeed);
	BuffApllied.Broadcast("SLOW",false,3);
}

void UStatsComponent::SlowRemove(float Amount)
{
	CurrentSpeed += Amount;
	OnSlowRemovedEvent.Broadcast(CurrentSpeed);
	BuffRemove.Broadcast("SLOW",false,3);
}

void UStatsComponent::Root()
{
	CurrentSpeed -= CurrentSpeed + 0;
	OnRootApplied.Broadcast();
	BuffApllied.Broadcast("ROOT",false,4);
}

void UStatsComponent::EndRoot(float Amount)
{
	CurrentSpeed = Amount;
	OnRootRemoved.Broadcast();
	BuffRemove.Broadcast("ROOT",false,4);
}

void UStatsComponent::Shield(float Amount)
{
	CurrentShield += BaseMaximumHealth * Amount;
	OnShieldApplied.Broadcast(Amount);
	BuffApllied.Broadcast("SHIELD",true,4);
}

void UStatsComponent::RemoveShield(float Amount)
{
	CurrentShield -= BaseMaximumHealth * Amount;
	if(CurrentShield < 0)
		CurrentShield = 0;
	
	OnShieldRemoved.Broadcast(Amount);
	BuffRemove.Broadcast("SHIELD",true,4);
}






