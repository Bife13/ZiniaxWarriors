// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Buff.h"
#include "Buffable.h"
#include "FBuffFactory.h"
#include "Components/ActorComponent.h"
#include "StatusEffectsComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class ZINIAXWARRIORS_API UStatusEffectsComponent : public UActorComponent, public IBuffable
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UStatusEffectsComponent();

	UFUNCTION(BlueprintCallable)
	void SetStatsComponent(UStatsComponent* StatsComponentToSet) {StatsComponent = StatsComponentToSet;}

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	const FBuffFactory* BuffFactory;
	TArray<IBuff*> CurrentBuffArray;
	UPROPERTY(EditAnywhere)
	float ArrayLength;

	UStatsComponent* StatsComponent;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
	UFUNCTION(BlueprintCallable)
	virtual void AddPowerBuff(float TimeAmount, float BuffAmount) override;
	UFUNCTION(BlueprintCallable)
	virtual void AddResistanceBuff(float TimeAmount, float BuffAmount) override;
};
