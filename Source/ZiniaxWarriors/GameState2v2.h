// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameMode2v2.h"
#include "GameFramework/GameState.h"
#include "GameState2v2.generated.h"


/**
 * 
 */
UCLASS()
class ZINIAXWARRIORS_API AGameState2v2 : public AGameState
{
	GENERATED_BODY()

	UPROPERTY()
	AGameMode2v2* GameMode;

	UFUNCTION()
	void BeginPlay() override;
	
public:
	UFUNCTION(BlueprintCallable)
	int GetTeam1Rounds()
	{
		return GameMode->GetTeam1RoundsWon();
	}

	UFUNCTION(BlueprintCallable)
	int GetTeam2Rounds()
	{
		return GameMode->GetTeam2RoundsWon();
	}

	UFUNCTION(BlueprintCallable)
	int GetRoundNumber()
	{
		return GameMode->GetRoundCount();
	}
	
	UFUNCTION(BlueprintCallable)
	int GetMinutes()
	{
		return GameMode->GetMinutes();
	}

	UFUNCTION(BlueprintCallable)
	int GetSeconds()
	{
		return GameMode->GetSeconds();
	}


};
