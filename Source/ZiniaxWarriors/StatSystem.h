// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Buffable.h"
#include "Components/ActorComponent.h"
#include "StatSystem.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ZINIAXWARRIORS_API UStatSystem : public UActorComponent , public IBuffable
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UStatSystem();

    virtual void DefenseUp(float Percentage,float Time) override;
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	UPROPERTY()
    float MaxDefenseUpTime;
	UPROPERTY()
	float defenseUpTimer;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(VisibleAnywhere)
	float Resistance;
	UPROPERTY()
	float BaseResistance;
		
};



