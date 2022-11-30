// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Buff.h"
#include "Buffable.h"
#include "FBuffFactory.h"
#include "Components/ActorComponent.h"
#include "StatusEffectsComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class ZINIAXWARRIORS_API UStatusEffectsComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UStatusEffectsComponent();
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
							   FActorComponentTickFunction* ThisTickFunction) override;
	void AddEnrage(float TimeAmount, float BuffAmount);
	void AddBulk(float TimeAmount, float BuffAmount);
	void AddHaste(float TimeAmount, float BuffAmount);
	void AddSlow(float TimeAmount, float DebuffAmount);
	void AddWeaken(float TimeAmount, float DebuffAmount);
	void AddVulnerable(float TimeAmount, float DebuffAmount);
	void AddRoot(float TimeAmount);
	void AddShield(float TimeAmount, float BuffAmount);
	void SetStatsComponent(UStatsComponent* StatsComponentToSet);
	

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	const FBuffFactory* BuffFactory;
	TArray<IBuff*> CurrentBuffArray;
	UPROPERTY(EditAnywhere)
	float ArrayLength;
    UPROPERTY()
 	UStatsComponent* StatsComponent;
	
	
};
	