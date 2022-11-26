// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StatsComponent.h"
#include "WorldWidget.h"
#include "Components/ActorComponent.h"
#include "Components/Widget.h"
#include "UI_Observer.generated.h"


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
	UWorldWidget* WorldWidget;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite);
	UHealthSystem* HealthSystemOfCharacter;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite);
	UStatsComponent* StatsSystemOfCharacter;
	
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void SetHealthSystem(UHealthSystem* HPComponent);
	UFUNCTION(BlueprintCallable)
	UHealthSystem* GetHealthSystem() const;
	UFUNCTION(BlueprintCallable)
	void SetStatsSystem(UStatsComponent* HPComponent);
	UFUNCTION(BlueprintCallable)
	UStatsComponent* GetStatsComponent();

	
	

	UFUNCTION(BlueprintCallable)
	UWorldWidget* GetWorldCharacterHPBar();
	void SetWorldWidget(UWorldWidget* WW);

};
