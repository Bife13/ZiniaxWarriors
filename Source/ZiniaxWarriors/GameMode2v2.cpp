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
	UClass* ClassToSpawn = SpawnableCharacters->FindRow<FSpawnableCharacter>(CharacterNames[0], "")->PlayableCharacter;
	if (SpawnedPlayer)
	{
		ClassToSpawn = SpawnableCharacters->FindRow<FSpawnableCharacter>(CharacterNames[0], "")->PlayableCharacter;
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
	UHealthSystem* CurrentHealthSystem = Cast<UHealthSystem>(
		PlayableCharacter->GetComponentByClass(UHealthSystem::StaticClass()));

	PlayableCharacter->SetSpawnLocation(Location);

	if (SpawnedPlayer)
	{
		PlayableCharacter->SetServerTeamId(2);
		Team2PlayerCharacters.Add(PlayableCharacter);
		Team2HealthComponents.Add(CurrentHealthSystem);
		PlayableCharacter->StartBeginPlay();
	}
	else
	{
		PlayableCharacter->SetServerTeamId(1);
		Team1PlayerCharacters.Add(PlayableCharacter);
		Team1HealthComponents.Add(CurrentHealthSystem);
		PlayableCharacter->StartBeginPlay();
	}

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


	return Super::InitNewPlayer(NewPlayerController, UniqueId, Options, Portal);
}

void AGameMode2v2::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (!bIsGameStarted && PlayerCounter >= 2)
	{
		bIsGameStarted = true;
	}

	if (bIsGameStarted)
	{
		for (int i = 0; i < Team1HealthComponents.Num(); i++)
		{
			if (Team1HealthComponents[i])
				Team1HealthComponents[i]->OnDeathEvent.AddUFunction(this, "Respawn", Team1PlayerCharacters[i],
				                                                    GetPlayerStartsForTeam1()[i]->GetActorLocation());
		}

		for (int i = 0; i < Team2HealthComponents.Num(); i++)
		{
			if (Team2HealthComponents[i])
				Team2HealthComponents[i]->OnDeathEvent.AddUFunction(this, "Respawn", Team2PlayerCharacters[i],
				                                                    GetPlayerStartsForTeam2()[i]->GetActorLocation());
		}
	}
}

void AGameMode2v2::Respawn(APlayableCharacter* CharacterToSpawn, FVector LocationToSpawn)
{
	CharacterToSpawn->SetActorLocation(LocationToSpawn);
	// TODO RESTART EVERYTHING

	CharacterToSpawn->ResetCharacter();
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
