// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WorldWidget.generated.h"

/**
 * 
 */
UCLASS()
class ZINIAXWARRIORS_API UWorldWidget : public UUserWidget
{
	GENERATED_BODY()

	// ReSharper disable once UnrealHeaderToolError
	public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly);
	class UHealthSystem* HealthSystemOfCharacter;

	UFUNCTION(BlueprintCallable)
	void SetHealthSystemOnWidget(UHealthSystem* Hp);
};
