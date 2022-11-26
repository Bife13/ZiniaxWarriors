// Fill out your copyright notice in the Description page of Project Settings.


#include "UI_Observer.h"

class UHealthSystem;
// Sets default values for this component's properties
UUI_Observer::UUI_Observer()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UUI_Observer::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
	
}

void UUI_Observer::SetHealthSystem(UHealthSystem* HPComponent)
{
	HealthSystemOfCharacter = HPComponent;
}

UHealthSystem* UUI_Observer::GetHealthSystem() const
{
	return HealthSystemOfCharacter;
}

void UUI_Observer::SetStatsSystem(UStatsComponent* Stats)
{
	StatsSystemOfCharacter = Stats;
}



UStatsComponent* UUI_Observer::GetStatsComponent()
{
	return StatsSystemOfCharacter;
}


UWorldWidget* UUI_Observer::GetWorldCharacterHPBar()
{
	return WorldWidget;
}

void UUI_Observer::SetWorldWidget(UWorldWidget* WW)
{
	WorldWidget =WW;
}


// Called every frame
void UUI_Observer::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}


