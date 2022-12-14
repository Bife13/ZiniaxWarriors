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
	UFUNCTION(Server, Unreliable)
	void TickArrays(float DeltaTime);
	// Called when the game starts
	virtual void BeginPlay() override;
	UFUNCTION()
	void AddEnrage(float TimeAmount, float BuffAmount);
	UFUNCTION()
	void AddBulk(float TimeAmount, float BuffAmount);
	UFUNCTION()
	void AddHaste(float TimeAmount, float BuffAmount);
	UFUNCTION()
	void AddSlow(float TimeAmount, float DebuffAmount);
	UFUNCTION()
	void AddWeaken(float TimeAmount, float DebuffAmount);
	UFUNCTION()
	void AddVulnerable(float TimeAmount, float DebuffAmount);
	UFUNCTION()
	void AddRoot(float TimeAmount);
	UFUNCTION()
	void AddShield(float TimeAmount, float BuffAmount);
	UFUNCTION()
	void AddCastingSlow(float TimeAmount, float BuffAmount);
	UFUNCTION()
	void SetStatsComponent(UStatsComponent* StatsComponentToSet);

	UFUNCTION()
	void CleanBuffs();


protected:
	const FBuffFactory* BuffFactory;

	UPROPERTY(Replicated)
	TArray<UObject*> CurrentBuffArray;
	TArray<IBuff*> CurrentBuffInterfaceArray;
	UPROPERTY()
	bool bIsCleaning = false;

	UPROPERTY(VisibleAnywhere, Replicated)
	float ArrayLength;
	UPROPERTY()
	UStatsComponent* StatsComponent;
};
