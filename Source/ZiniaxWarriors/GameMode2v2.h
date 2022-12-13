// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
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
	TArray<APlayerStart*> GetPlayerStartsForTeam1();
	TArray<APlayerStart*> GetPlayerStartsForTeam2();
	void CachePlayerStarts();

private:
	TArray<AActor*> PlayerStarts;
	TArray<APlayableCharacter*> PlayerCharacters;

	bool SpawnedPlayer = false;
	int CurrentStart = 0;

	int PlayerCounter = 0;

	UPROPERTY(EditDefaultsOnly, meta=(AllowPrivateAccess))
	UDataTable* SpawnableCharacters;
};
