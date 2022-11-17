// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "SkillActor.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class USkillActor : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class ZINIAXWARRIORS_API ISkillActor
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	int GetTeam();
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	float GetDamage();
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	float GetRange();
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	FVector GetSpawnPosition();
	
	UFUNCTION(BlueprintImplementableEvent)
	void SetTeam(int Value);
	UFUNCTION(BlueprintImplementableEvent)
	void SetDamage(float Value);
	UFUNCTION(BlueprintImplementableEvent)
	void SetRange(float Value);
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void SetSpawnPosition(FVector SpawnPosition);
};
