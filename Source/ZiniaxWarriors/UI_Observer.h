// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StatsComponent.h"
#include "WorldWidget.h"
#include "Components/ActorComponent.h"
#include "Components/Widget.h"
#include "UI_Observer.generated.h"


class UDataTable;
class UHealthSystem;
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ZINIAXWARRIORS_API UUI_Observer : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UUI_Observer();
protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite);
	UWorldWidget* WorldCharacterHPBar;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite);
	UHealthSystem* HealthSystemOfCharacter;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite);
	UStatsComponent* StatsSystemOfCharacter;
	
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void SetHealthSystem(UHealthSystem* HPComponent);
	void SetStatsSystem(UStatsComponent* HPComponent);

	UFUNCTION(BlueprintCallable)
	void SetWorldHPBar(UWorldWidget* HPBAr);
	UFUNCTION(BlueprintCallable)
	UWorldWidget* GetWorldCharacterHPBar();
	
	
};
