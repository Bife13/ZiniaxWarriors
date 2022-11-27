// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HealthSystem.h"
#include "Blueprint/UserWidget.h"
#include "WorldWidget.generated.h"

/**
 * 
 */
UCLASS()
class ZINIAXWARRIORS_API UWorldWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite)
	UHealthSystem* WW_HPSystem;

	UFUNCTION(BlueprintCallable)
	void WW_SetHPSystem(UHealthSystem* Hp);
	UFUNCTION(BlueprintCallable,BlueprintNativeEvent)
	float GetDamageNumber(float damage);

	UFUNCTION(BlueprintCallable,BlueprintNativeEvent)
	void OnDamage();

};
