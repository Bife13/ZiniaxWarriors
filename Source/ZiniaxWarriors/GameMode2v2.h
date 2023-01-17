// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePlayerController.h"
#include "GameState2v2.h"
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
	virtual void BeginPlay() override;
	virtual FString InitNewPlayer(APlayerController* NewPlayerController, const FUniqueNetIdRepl& UniqueId,
	                              const FString& Options, const FString& Portal) override;
	virtual void Tick(float DeltaSeconds) override;

	virtual bool ReadyToStartMatch_Implementation() override;

	static FString ParsingWarriorName(const FString& Options);
	static FString ParsingAbility1(const FString& Options);
	static FString ParsingAbility2(const FString& Options);
	static FString ParsingAbility3(const FString& Options);
	

	
	UFUNCTION()
	void SetDeathEvents();
	UFUNCTION()
	void RespawnCharacters();
	UFUNCTION()
	void CountDeath(int TeamId, ABasePlayerController* DeadCharacterController, APlayableCharacter* DeadCharacter);
	UFUNCTION()
	bool CheckRoundCounter();

	UFUNCTION()
	void SetCanDoorOpenTrue() { bCanDoorOpen = true; }

	UFUNCTION()
	void SetCanDoorOpenFalse() { bCanDoorOpen = false; }

	UPROPERTY()
	bool bCanDoorOpen = false;

	FSocket* Socket;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString PlayerName;
	// For Server just send " |";
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString PlayerPass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString IpString;


	UFUNCTION()
	TArray<APlayerStart*> GetPlayerStartsForTeam1();
	UFUNCTION()
	TArray<APlayerStart*> GetPlayerStartsForTeam2();
	UFUNCTION()
	void CachePlayerStarts();
	UFUNCTION()
	void CacheDoors();

	UFUNCTION()
	void StartInBetweenRoundTimer(float Time);
	UFUNCTION()
	void StartDoorTimer(float Time);
	UFUNCTION()
	void RestartGameAfterDelay(float Time);
	UFUNCTION()
	void RespawnAfterDelay(float Time);
	UFUNCTION()
	void RestartServerAfterDelay(float Time);

	UFUNCTION()
	void ActivateAllCharacters();
	UFUNCTION()
	void DeactivateAllCharacters();

	UFUNCTION()
	void OpenDoors(float DeltaTime);
	UFUNCTION()
	void CloseDoors();
	UFUNCTION()
	void SendPlayersToLogin();
	UFUNCTION()
	void RestartServer();

	UFUNCTION(BlueprintImplementableEvent)
	void MatchTimer();

	UFUNCTION(BlueprintImplementableEvent)
	void StartMatchMusicEvent();
	
	UPROPERTY(BlueprintReadWrite)
	int Minutes = 1;
	UPROPERTY(BlueprintReadWrite)
	int Seconds = 30.f;
	UFUNCTION()
	void SetMinutesInGameState();
	UFUNCTION()
	void SetSecondsInGameState();
	UFUNCTION()
	void SetRoundCountInGameState();
	UFUNCTION()
	void SetTeam1RoundsWonInGameState();
	UFUNCTION()
	void SetTeam2RoundsWonInGameState();
	UFUNCTION()
	void UpdateRoundsInGameState();
	UFUNCTION(BlueprintCallable)
	void UpdateGameTimer();

	UPROPERTY(BlueprintReadWrite)
	TArray<APlayableCharacter*> Team1PlayerCharacters;
	UPROPERTY(BlueprintReadWrite)
	TArray<APlayableCharacter*> Team2PlayerCharacters;
private:
	UPROPERTY()
	AGameState2v2* GameState2v2;

	UPROPERTY()
	TArray<AActor*> PlayerStarts;
	UPROPERTY()
	TArray<AActor*> SpawnDoors;
	UPROPERTY()
	TArray<ABasePlayerController*> PlayerControllers;
	UPROPERTY()
	TArray<UHealthSystem*> Team1HealthComponents;
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

	UPROPERTY(EditAnywhere)
	int MaxPlayers;

	UPROPERTY(VisibleAnywhere)
	int Team1DeathCounter = 0;
	UPROPERTY(VisibleAnywhere)
	int Team2DeathCounter = 0;

	UPROPERTY(VisibleAnywhere)
	int RoundCounter = 1;
	UPROPERTY(VisibleAnywhere)
	int Team1RoundsWon = 0;
	UPROPERTY(VisibleAnywhere)
	int Team2RoundsWon = 0;

	UPROPERTY(VisibleAnywhere)
	int DelayAfterRoundEnd = 5;
	UPROPERTY(VisibleAnywhere)
	int DelayAfterGameEnd = 15;
	UPROPERTY(VisibleAnywhere)
	int DelayBetweenRounds = 3;
	


	UPROPERTY(EditDefaultsOnly, meta=(AllowPrivateAccess))
	UDataTable* SpawnableCharacters;

	UPROPERTY(EditDefaultsOnly, meta=(AllowPrivateAccess))
	UDataTable* SkillsDatatable;
};
