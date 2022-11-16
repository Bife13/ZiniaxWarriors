// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Damageable.h"
#include "HealthSystem.generated.h"

DECLARE_EVENT_OneParam(UCPP_HealthSystem, DamageTakenEvent, float)
DECLARE_EVENT_OneParam(UCPP_HealthSystem, HealDamageEvent, float)

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class ZINIAXWARRIORS_API UHealthSystem : public UActorComponent , public IDamageable
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UHealthSystem();
	//Gets
	UFUNCTION(BlueprintPure)
	float GetHealth() const;
	UFUNCTION(BlueprintPure)
	float GetMaxHealth() const;
	UFUNCTION(BlueprintPure)
	float GetHealthAsPercentage() const;
	//General functions
	UFUNCTION(BlueprintCallable)
	virtual void TakeDamage(float Amount) override;
	UFUNCTION(BlueprintCallable)
	void RecoverHealth(float Amount);
	//Sets
	UFUNCTION(BlueprintCallable)
	void SetHealthToMaxHealth();
	UFUNCTION(BlueprintCallable)
	void SetMaxHealth(float Amount);
	UFUNCTION(BlueprintCallable)
	void SetResistance(float Amount);
	
protected: // Functions

	virtual void BeginPlay() override;

public: // Events

	DamageTakenEvent OnDamageTakenEvent;
	HealDamageEvent OnDamageHealedEvent;

private: // This can be protected if we want to subclass the Health Component

	UPROPERTY(VisibleAnywhere)
	float Health;
	float MaxHealth;
	UPROPERTY(VisibleAnywhere)
	float Resistance;
};
