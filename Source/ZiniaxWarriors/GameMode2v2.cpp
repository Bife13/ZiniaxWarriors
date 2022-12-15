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
	UClass* ClassToSpawn = SpawnableCharacters->FindRow<FSpawnableCharacter>(CharacterNames[CharIndex], "")->PlayableCharacter;
	if (SpawnedPlayer)
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
	PlayerControllers.Add(Cast<ABasePlayerController>(NewPlayerController));
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
}

bool AGameMode2v2::ReadyToStartMatch_Implementation()
{
	SetDeathEvents();

	if (GetMatchState() == MatchState::WaitingToStart)
	{
		if (PlayerCounter >= 2)
		{
			StartInBetweenRoundTimer(1);
			return true;
		}
	}
	return false;
}

void AGameMode2v2::StartInBetweenRoundTimer(float Time)
{
	FTimerHandle UnusedHandle;
	GetWorldTimerManager().SetTimer(
		UnusedHandle, this, &AGameMode2v2::ActivateAllCharacters, Time, false);
}

void AGameMode2v2::ActivateAllCharacters()
{
	for (int i = 0; i < PlayerControllers.Num(); i++)
	{
		PlayerControllers[i]->CharacterActivate();
	}
}

void AGameMode2v2::DeactivateAllCharacters()
{
	for (int i = 0; i < PlayerControllers.Num(); i++)
	{
		PlayerControllers[i]->CharacterDeactivate();
	}
}


void AGameMode2v2::SetDeathEvents()
{
	if (!bIsGameStarted && PlayerCounter >= 2)
	{
		bIsGameStarted = true;
		for (int i = 0; i < Team1HealthComponents.Num(); i++)
		{
			if (Team1HealthComponents[i])
				Team1HealthComponents[i]->OnDeathEvent.AddUFunction(this, "CountDeath", 1,
				                                                    Team1PlayerCharacters[i]->GetController());
		}

		for (int i = 0; i < Team2HealthComponents.Num(); i++)
		{
			if (Team2HealthComponents[i])
				Team2HealthComponents[i]->OnDeathEvent.AddUFunction(this, "CountDeath", 2,
				                                                    Team2PlayerCharacters[i]->GetController());
		}
	}
}

void AGameMode2v2::RespawnCharacters()
{
	DeactivateAllCharacters();

	for (int i = 0; i < Team1PlayerCharacters.Num(); i++)
	{
		Team1PlayerCharacters[i]->SetActorLocation(GetPlayerStartsForTeam1()[i]->GetActorLocation());
		Team1PlayerCharacters[i]->ResetCharacter();
	}

	for (int i = 0; i < Team2PlayerCharacters.Num(); i++)
	{
		Team2PlayerCharacters[i]->SetActorLocation(GetPlayerStartsForTeam2()[i]->GetActorLocation());
		Team2PlayerCharacters[i]->ResetCharacter();
	}
}

void AGameMode2v2::CountDeath(int TeamId, ABasePlayerController* DeadCharacterController)
{
	if (TeamId == 1)
	{
		Team1DeathCounter++;
		DeadCharacterController->CharacterDeactivate();
	}
	else
	{
		Team2DeathCounter++;
		DeadCharacterController->CharacterDeactivate();
	}

	if (Team1DeathCounter >= Team1PlayerCharacters.Num() || Team2DeathCounter >= Team2PlayerCharacters.Num())
	{
		RespawnCharacters();
		RoundCounter++;
		if (Team1DeathCounter >= Team1PlayerCharacters.Num())
			Team2RoundsWon++;
		else if (Team2DeathCounter >= Team2PlayerCharacters.Num())
			Team1RoundsWon++;
		if (!CheckRoundCounter())
		{
			StartInBetweenRoundTimer(1);
			Team1DeathCounter = Team2DeathCounter = 0;
		}
	}
}

bool AGameMode2v2::CheckRoundCounter()
{
	if (Team1RoundsWon >= 3)
	{
		GEngine->AddOnScreenDebugMessage(1, 2, FColor::Black, "Team 1 Won");
		DeactivateAllCharacters();
		return true;
	}
	else if (Team2RoundsWon >= 3)
	{
		GEngine->AddOnScreenDebugMessage(1, 2, FColor::Black, "Team 2 Won");
		DeactivateAllCharacters();
		return true;
	}
	return false;
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
