// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HealthSystem.h"
#include "UI_Observer.h"
#include "Components/ProgressBar.h"
#include "WorldWidget.generated.h"

class UUI_Observer;
/**
 * 
 */
UCLASS()
class ZINIAXWARRIORS_API UWorldWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable)
	void WorldWigetSetUp(UProgressBar* Bar,UUI_Observer* Obs);
	


	UFUNCTION(BlueprintCallable)
	void UpdateHPBar();
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UProgressBar* HPBAr;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UUI_Observer* Observer;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UHealthSystem* HealthSystem;
	// ReSharper disable once UnrealHeaderToolError
	protected:

	


	
};
