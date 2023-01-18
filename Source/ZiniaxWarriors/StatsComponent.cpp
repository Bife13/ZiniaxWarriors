// Fill out your copyright notice in the Description page of Project Settings.


#include "StatsComponent.h"

#include "Net/UnrealNetwork.h"

// Sets default values for this component's properties
UStatsComponent::UStatsComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

void UStatsComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(UStatsComponent, CurrentPower);
	DOREPLIFETIME(UStatsComponent, CurrentResistance);
	DOREPLIFETIME(UStatsComponent, CurrentShield);
	DOREPLIFETIME(UStatsComponent, CurrentSpeed);
	DOREPLIFETIME(UStatsComponent, CurrentMaximumHealth);
	DOREPLIFETIME(UStatsComponent, CurrentViewRange);
}


void UStatsComponent::HandleShieldAppliedEvent_Implementation(float Amount)
{
	OnShieldApplied.Broadcast(CurrentShield);
	BuffApllied.Broadcast("SHIELD", true, 4, GetPower(),GetResistance(),GetSpeed(),GetViewRange());
}

void UStatsComponent::HandleShieldRemovedEvent_Implementation(float Amount)
{
	OnShieldRemoved.Broadcast(CurrentShield);
	BuffRemove.Broadcast("SHIELD", true, 4,GetPower(),GetResistance(),GetSpeed(),GetViewRange());
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

void UStatsComponent::SetupStatSystem_Implementation(float PowerValue, float SpeedValue, float MaximumHealthValue,
                                                     float ResistanceValue,
                                                     float ViewRangeValue)
{
	BaseSpeed = SpeedValue;
	BasePower = PowerValue;
	BaseMaximumHealth = MaximumHealthValue;
	BaseResistance = ResistanceValue;
	BaseViewRange = ViewRangeValue;

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
	HandleEnrageEvents(Amount);
}

void UStatsComponent::HandleEnrageEvents_Implementation(float Amount)
{
	if (Amount > 0)
	{
		OnEnrageAppliedEvent.Broadcast(CurrentPower);
		BuffApllied.Broadcast("ENRAGE", true, 1,GetPower(),GetResistance(),GetSpeed(),GetViewRange());
	}
	else
	{
		OnEnrageRemovedEvent.Broadcast(CurrentPower);
		BuffRemove.Broadcast("ENRAGE", true, 1,GetPower(),GetResistance(),GetSpeed(),GetViewRange());
	}
}

void UStatsComponent::Weaken(float Amount)
{
	CurrentPower -= (BasePower * Amount);
	HandleWeakenEvents(Amount);
}

void UStatsComponent::HandleWeakenEvents_Implementation(float Amount)
{
	if (Amount > 0)
	{
		OnWeakenAppliedEvent.Broadcast(CurrentPower);
		BuffApllied.Broadcast("WEAKEN", false, 1,GetPower(),GetResistance(),GetSpeed(),GetViewRange());
	}
	else
	{
		OnWeakenRemovedEvent.Broadcast(CurrentPower);
		BuffRemove.Broadcast("WEAKEN", false, 1,GetPower(),GetResistance(),GetSpeed(),GetViewRange());
	}
}

void UStatsComponent::Bulk(float Amount)
{
	CurrentResistance += (BaseResistance * Amount);
    HandleBulkEvents(Amount);
}

void UStatsComponent::HandleBulkEvents_Implementation(float Amount)
{
	if (Amount > 0)
	{
		OnBulkAppliedEvent.Broadcast(CurrentResistance);
		BuffApllied.Broadcast("BULK", true, 2,GetPower(),GetResistance(),GetSpeed(),GetViewRange());
	}
	else
	{
		OnBulkRemovedEvent.Broadcast(CurrentResistance);
		BuffRemove.Broadcast("BULK", true, 2,GetPower(),GetResistance(),GetSpeed(),GetViewRange());
	}
}

void UStatsComponent::Vulnerable(float Amount)
{
	CurrentResistance -= (BaseResistance * Amount);
	HandleVulnerableEvents(Amount);
}

void UStatsComponent::HandleVulnerableEvents_Implementation(float Amount)
{
	if (Amount > 0)
	{
		OnVulnerableAppliedEvent.Broadcast(CurrentResistance);
		BuffApllied.Broadcast("VULNERABLE", false, 2,GetPower(),GetResistance(),GetSpeed(),GetViewRange());
	}
	else
	{
		OnVulnerableRemovedEvent.Broadcast(CurrentResistance);
		BuffRemove.Broadcast("VULNERABLE", false, 2,GetPower(),GetResistance(),GetSpeed(),GetViewRange());
	}
}

void UStatsComponent::Haste(float Amount)
{
	CurrentSpeed += (CurrentSpeed * Amount);
	HandleHasteEventsApplied(GetPower(),GetResistance(),GetSpeed(),GetViewRange(),CurrentSpeed);
}

void UStatsComponent::HasteRemove(float Amount)
{
	CurrentSpeed -= Amount;
	HandleHasteEventsRemove(GetPower(),GetResistance(),GetSpeed(),GetViewRange(), Amount);
}

void UStatsComponent::HandleHasteEventsRemove_Implementation(float CurrentP, float CurrentR, float CurrentS, float CurrentVR, float Amount)
{
	OnHasteRemovedEvent.Broadcast(Amount);
	BuffRemove.Broadcast("HASTE", true, 3,CurrentP, CurrentR,CurrentS, CurrentVR);
}

void UStatsComponent::HandleHasteEventsApplied_Implementation(float CurrentP, float CurrentR, float CurrentS, float CurrentVR, float Amount)
{
	OnHasteAppliedEvent.Broadcast(Amount);
	BuffApllied.Broadcast("HASTE", true, 3,CurrentP, CurrentR, CurrentS, CurrentVR);
}

void UStatsComponent::Slow(float Amount)
{
	CurrentSpeed -= (CurrentSpeed * Amount);
	HandleSlowAppliedEvent(GetPower(),GetResistance(),GetSpeed(),GetViewRange(),CurrentSpeed);
}

void UStatsComponent::SlowRemove(float Amount)
{
	CurrentSpeed += Amount;
	HandleSlowRemoveEvent(GetPower(),GetResistance(),GetSpeed(),GetViewRange(),Amount);
}

void UStatsComponent::HandleSlowAppliedEvent_Implementation(float CurrentP, float CurrentR, float CurrentS, float CurrentVR, float Amount)
{
	OnSlowAppliedEvent.Broadcast(Amount);
	BuffApllied.Broadcast("SLOW", false, 3,CurrentP, CurrentR, CurrentS, CurrentVR);
}

void UStatsComponent::HandleSlowRemoveEvent_Implementation(float CurrentP, float CurrentR, float CurrentS, float CurrentVR, float Amount)
{
	OnSlowRemovedEvent.Broadcast(Amount);
	BuffRemove.Broadcast("SLOW", false, 3,CurrentP, CurrentR, CurrentS, CurrentVR);
}

void UStatsComponent::Root()
{
	CurrentSpeed -= CurrentSpeed + 0;
	HandleRootAppliedEvent();
}

void UStatsComponent::EndRoot(float Amount)
{
	CurrentSpeed = Amount;
    HandleRootRemovedEvent();
}

void UStatsComponent::HandleRootAppliedEvent_Implementation()
{
	OnRootApplied.Broadcast();
	BuffApllied.Broadcast("ROOT", false, 4,GetPower(),GetResistance(),GetSpeed(),GetViewRange());
}

void UStatsComponent::HandleRootRemovedEvent_Implementation()
{
	OnRootRemoved.Broadcast();
	BuffRemove.Broadcast("ROOT", false, 4,GetPower(),GetResistance(),GetSpeed(),GetViewRange());
}

void UStatsComponent::Shield(float Amount)
{
	CurrentShield += BaseMaximumHealth * Amount;
	HandleShieldAppliedEvent(CurrentShield);
}

void UStatsComponent::RemoveShield(float Amount)
{
	CurrentShield -= BaseMaximumHealth * Amount;
	if (CurrentShield < 0)
		CurrentShield = 0;

    HandleShieldRemovedEvent(CurrentShield);
}
