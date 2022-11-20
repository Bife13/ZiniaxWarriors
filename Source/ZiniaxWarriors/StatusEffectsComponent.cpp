// Fill out your copyright notice in the Description page of Project Settings.


#include "StatusEffectsComponent.h"

#include "FBuffFactory.h"
#include "PowerBuff.h"
#include "ResistanceBuff.h"

UStatusEffectsComponent::UStatusEffectsComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

void UStatusEffectsComponent::BeginPlay()
{
	Super::BeginPlay();
	BuffFactory = new FBuffFactory();
	AddResistanceBuff();
	AddPowerBuff();
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
					CurrentBuffArray[i]->OnBuffBegin();
				}

				float Timer = CurrentBuffArray[i]->GetTimer();
				Timer -= DeltaTime;
				CurrentBuffArray[i]->SetTimer(Timer);
				if (CurrentBuffArray[i]->GetTimer() <= 0)
				{
					CurrentBuffArray[i]->OnBuffEnd();
					CurrentBuffArray.RemoveAt(i);
				}
			}
		}
	}

	ArrayLength = CurrentBuffArray.Num();
}

void UStatusEffectsComponent::AddPowerBuff()
{
	CurrentBuffArray.Add(BuffFactory->CreateBuff<UPowerBuff>());
}

void UStatusEffectsComponent::AddResistanceBuff()
{
	CurrentBuffArray.Add(BuffFactory->CreateBuff<UResistanceBuff>());
}
