// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "GameFramework/GameModeBase.h"
#include "NetworkedGameModeBase.generated.h"

class APlayerStart;
/**
 * 
 */
UCLASS()
class ZINIAXWARRIORS_API ANetworkedGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

protected:

	virtual FString InitNewPlayer(APlayerController* NewPlayerController, const FUniqueNetIdRepl& UniqueId, const FString& Options, const FString& Portal) override;
	
	TArray<APlayerStart*> GetPlayerStartsForTeam1();
	TArray<APlayerStart*> GetPlayerStartsForTeam2();
	void CachePlayerStarts();

private:
	TArray<AActor*> PlayerStarts;
	
	bool SpawnedPlayer = false;
	int CurrentStart = 0;

	UPROPERTY(EditDefaultsOnly, meta=(AllowPrivateAccess))
	UDataTable* SpawnableCharacters;
	
};
