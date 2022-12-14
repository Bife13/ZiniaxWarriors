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

	UFUNCTION()
	static void Respawn(APlayableCharacter* CharacterToSpawn,FVector LocationToSpawn );
	
	UFUNCTION()
	TArray<APlayerStart*> GetPlayerStartsForTeam1();
	UFUNCTION()
	TArray<APlayerStart*> GetPlayerStartsForTeam2();
	UFUNCTION()
	void CachePlayerStarts();

private:
	UPROPERTY()
	TArray<AActor*> PlayerStarts;
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

	UPROPERTY(EditDefaultsOnly, meta=(AllowPrivateAccess))
	UDataTable* SpawnableCharacters;
};
