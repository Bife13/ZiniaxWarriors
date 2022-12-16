// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Blueprint/UserWidget.h"
#include "Cpp_CustomizationWidget.generated.h"

/**
 * 
 */
UCLASS()
class ZINIAXWARRIORS_API UCpp_CustomizationWidget : public UUserWidget
{
	GENERATED_BODY()

	public:
	
	
	UPROPERTY(BlueprintReadWrite)
	int WarriorID= -1;
	
	UPROPERTY(BlueprintReadWrite)
	int Ability1ID= -1;
	
	UPROPERTY(BlueprintReadWrite)
	int Ability2ID= -1;
	
	UPROPERTY(BlueprintReadWrite)
	int Ability3ID= -1;

	UFUNCTION(BlueprintCallable)
	void SetAbility(int number,int index);
	UFUNCTION(BlueprintCallable)
	int GetAbility(int number);
	UFUNCTION()
	FString GetConfigInString();
	UFUNCTION(BlueprintCallable)
	void SetWarrior(int index);
	
	UFUNCTION(BlueprintCallable)
	bool IsWarriorSetUp();
};
