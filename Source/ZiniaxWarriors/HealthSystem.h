// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthSystem.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FHealDamageEvent,float,Cpp_HealingValue);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDamageTakenEvent,float,Cpp_Damage);


DECLARE_EVENT_OneParam(UHealthSystem,ShieldBrokenEvent,float)
DECLARE_EVENT(UHealthSystem,Die)



UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class ZINIAXWARRIORS_API UHealthSystem : public UActorComponent
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
	UFUNCTION(BlueprintCallable,Server,Reliable)
	void TakeDamage(float Amount);
	UFUNCTION(NetMulticast,Reliable)
	void HandleShieldBrokenEvent(float Amount);
	UFUNCTION(NetMulticast,Reliable)
	void HandleDamageTakenEvent(float Amount);
	UFUNCTION(NetMulticast,Reliable)
	void HandleHealEvent(float Amount);
	UFUNCTION(BlueprintCallable, Server, Reliable)
	void RecoverHealth(float Amount);
	//Sets
	UFUNCTION(BlueprintCallable)
	void SetHealthToMaxHealth();
	UFUNCTION()
	void SetMaxHealth(float Amount);
	UFUNCTION(BlueprintCallable)
	void SetResistance(float Amount);
	UFUNCTION(Server, Reliable)
	void SetShield(float Amount);
	UFUNCTION(BlueprintCallable)
	float GetShield() const{return Shield;}
	UFUNCTION()
	void ResetHealth();
	

protected: // Functions

	virtual void BeginPlay() override;

	
public: // Events

	UPROPERTY(BlueprintAssignable)
	FDamageTakenEvent MyOnDamageTakenEvent;
	UPROPERTY(BlueprintAssignable)
	FHealDamageEvent OnDamageHealedEvent;

	ShieldBrokenEvent OnShieldBrokenEvent;
	Die OnDeathEvent;
	
private: // This can be protected if we want to subclass the Health Component

	UPROPERTY(VisibleAnywhere,Replicated)
	float Shield;
	UPROPERTY(VisibleAnywhere, Replicated)
	float Health;
	UPROPERTY(VisibleAnywhere)
	float MaxHealth;
	UPROPERTY(VisibleAnywhere)
	float Resistance;
};
