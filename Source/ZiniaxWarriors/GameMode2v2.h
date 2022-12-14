// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePlayerController.h"
#include "PlayableCharacter.h"
#include "Engine/DataTable.h"
#include "GameFramework/GameMode.h"
#include "GameMode2v2.generated.h"

class APlayerStart;
/**
 * 
 */
UCLASS()
class ZINIAXWARRIORS_API AGameMode2v2 : public AGameMode
{
	GENERATED_BODY()

protected:
	virtual FString InitNewPlayer(APlayerController* NewPlayerController, const FUniqueNetIdRepl& UniqueId,
	                              const FString& Options, const FString& Portal) override;
	virtual void Tick(float DeltaSeconds) override;

	virtual bool ReadyToStartMatch_Implementation() override;


	UFUNCTION()
	void SetDeathEvents();
	UFUNCTION()
	void RespawnCharacters();
	UFUNCTION()
	void CountDeath(int TeamId);
	UFUNCTION()
	bool CheckRoundCounter();

	UFUNCTION()
	TArray<APlayerStart*> GetPlayerStartsForTeam1();
	UFUNCTION()
	TArray<APlayerStart*> GetPlayerStartsForTeam2();
	UFUNCTION()
	void CachePlayerStarts();

	UFUNCTION()
	void StartInBetweenRoundTimer(float Time);
	UFUNCTION()
	void ActivateAllCharacters();
	UFUNCTION()
	void DeactivateAllCharacters();

private:
	UPROPERTY()
	TArray<AActor*> PlayerStarts;
	UPROPERTY()
	TArray<ABasePlayerController*> PlayerControllers;
	UPROPERTY()
	TArray<APlayableCharacter*> Team1PlayerCharacters;
	UPROPERTY()
	TArray<UHealthSystem*> Team1HealthComponents;
	UPROPERTY()
	TArray<APlayableCharacter*> Team2PlayerCharacters;
	UPROPERTY()
	TArray<UHealthSystem*> Team2HealthComponents;

	UPROPERTY()
	bool SpawnedPlayer = false;
	UPROPERTY()
	int CurrentStart = 0;
	UPROPERTY()
	int PlayerCounter = 0;
	UPROPERTY()
	bool bIsGameStarted = false;

	UPROPERTY(VisibleAnywhere)
	int Team1DeathCounter = 0;
	UPROPERTY(VisibleAnywhere)
	int Team2DeathCounter = 0;

	UPROPERTY()
	int RoundCounter = 0;
	UPROPERTY()
	int Team1RoundsWon = 0;
	UPROPERTY()
	int Team2RoundsWon = 0;

	
	
	UPROPERTY(EditDefaultsOnly, meta=(AllowPrivateAccess))
	UDataTable* SpawnableCharacters;

};

