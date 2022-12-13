// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode2v2.h"

#include "BasePlayerController.h"
#include "DTR_SpawnableCharacter.h"
#include "GameState2v2.h"
#include "GameFramework/PlayerStart.h"
#include "Kismet/GameplayStatics.h"

FString AGameMode2v2::InitNewPlayer(APlayerController* NewPlayerController, const FUniqueNetIdRepl& UniqueId,
                                    const FString& Options, const FString& Portal)
{
	APlayerStart* PlayerStart = GetPlayerStartsForTeam1()[CurrentStart];
	if (SpawnedPlayer)
	{
		PlayerStart = GetPlayerStartsForTeam2()[CurrentStart];
	}

	UE_LOG(LogTemp, Warning, TEXT("Picked StartPointNamed: %s"), *PlayerStart->GetName());

	TArray<FName> CharacterNames = {"Nyax", "Drex", "Zerher"};

	// Spawn An Actor												// Nyax, Drex, Zerher

	int CharIndex = FMath::RandRange(0, 2);
	UClass* ClassToSpawn = SpawnableCharacters->FindRow<FSpawnableCharacter>(CharacterNames[2], "")->PlayableCharacter;
	if (SpawnedPlayer)
	{
		ClassToSpawn = SpawnableCharacters->FindRow<FSpawnableCharacter>(CharacterNames[2], "")->PlayableCharacter;
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
	if (SpawnedPlayer)
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

	if (SpawnedPlayer)
	{
		CurrentStart++;
		SpawnedPlayer = false;
	}
	else
	{
		SpawnedPlayer = true;
	}

	++PlayerCounter;

	if(PlayerCounter == 4)
	{
		GEngine->AddOnScreenDebugMessage(1,2,FColor::Green, "All Players Here");
	}

	PlayerCharacters.Add(PlayableCharacter);
	
	return Super::InitNewPlayer(NewPlayerController, UniqueId, Options, Portal);
}



TArray<APlayerStart*> AGameMode2v2::GetPlayerStartsForTeam1()
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

TArray<APlayerStart*> AGameMode2v2::GetPlayerStartsForTeam2()
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

void AGameMode2v2::CachePlayerStarts()
{
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerStart::StaticClass(), PlayerStarts);
}
