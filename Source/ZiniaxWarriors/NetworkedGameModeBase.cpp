// Fill out your copyright notice in the Description page of Project Settings.


#include "NetworkedGameModeBase.h"

#include "BasePlayerController.h"
#include "DTR_SpawnableCharacter.h"
#include "GameFramework/PlayerStart.h"
#include "Kismet/GameplayStatics.h"


FString ANetworkedGameModeBase::InitNewPlayer(APlayerController* NewPlayerController, const FUniqueNetIdRepl& UniqueId,
                                              const FString& Options, const FString& Portal)
{
	APlayerStart* PlayerStart = GetPlayerStartsForTeam1()[CurrentStart];
	if (SpawnedTeam1)
	{
		PlayerStart = GetPlayerStartsForTeam2()[CurrentStart];
	}

	UE_LOG(LogTemp, Warning, TEXT("Picked StartPointNamed: %s"), *PlayerStart->GetName());

	TArray<FName> CharacterNames = {"Nyax", "Drex", "Zerher"};

	// Spawn An Actor												// Nyax, Drex, Zerher

	int CharIndex = FMath::RandRange(0,2);
	UClass* ClassToSpawn = SpawnableCharacters->FindRow<FSpawnableCharacter>(CharacterNames[CharIndex], "")->PlayableCharacter;
	if (SpawnedTeam1)
	{
		ClassToSpawn = SpawnableCharacters->FindRow<FSpawnableCharacter>(CharacterNames[CharIndex], "")->PlayableCharacter;
	}

	FVector Location = PlayerStart->GetActorLocation();
	FRotator Rotation = PlayerStart->GetActorRotation();
	FActorSpawnParameters spawnParams;

	spawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	ACharacter* SpawnedActor = Cast<
		ACharacter>(GetWorld()->SpawnActor(ClassToSpawn, &Location, &Rotation, spawnParams));

	NewPlayerController->ClientSetLocation(Location, Rotation);

	
	NewPlayerController->Possess(SpawnedActor);
	SpawnedActor->SetOwner(NewPlayerController);
	APlayableCharacter* PlayableCharacter = Cast<APlayableCharacter>(SpawnedActor);
	PlayableCharacter->SetSpawnLocation(Location);
	if (SpawnedTeam1)
	{
		PlayableCharacter->SetServerTeamId(2);
		PlayableCharacter->StartBeginPlay();
	}
	else
	{
		PlayableCharacter->SetServerTeamId(1);
		PlayableCharacter->StartBeginPlay();
	}

	// Cast<ABasePlayerController>(NewPlayerController)->OnCharacterPossess(SpawnedActor);

	CurrentStart++;

	if (CurrentStart > 1)
	{
		SpawnedTeam1 = true;
		CurrentStart = 0;
	}

	return Super::InitNewPlayer(NewPlayerController, UniqueId, Options, Portal);
}

TArray<APlayerStart*> ANetworkedGameModeBase::GetPlayerStartsForTeam1()
{
	if (PlayerStarts.Num() == 0)
		CachePlayerStarts();

	TArray<APlayerStart*> Team1PlayerStarts;

	for (int i = 0; i < PlayerStarts.Num(); ++i)
	{
		if (PlayerStarts[i]->Tags.Contains("Team1"))
		{
			Team1PlayerStarts.Add(Cast<APlayerStart>(PlayerStarts[i]));
		}
	}
	return Team1PlayerStarts;
}

TArray<APlayerStart*> ANetworkedGameModeBase::GetPlayerStartsForTeam2()
{
	if (PlayerStarts.Num() == 0)
		CachePlayerStarts();

	TArray<APlayerStart*> Team2PlayerStarts;

	for (int i = 0; i < PlayerStarts.Num(); ++i)
	{
		if (PlayerStarts[i]->Tags.Contains("Team2"))
		{
			Team2PlayerStarts.Add(Cast<APlayerStart>(PlayerStarts[i]));
		}
	}
	return Team2PlayerStarts;
}

void ANetworkedGameModeBase::CachePlayerStarts()
{
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerStart::StaticClass(), PlayerStarts);
}
