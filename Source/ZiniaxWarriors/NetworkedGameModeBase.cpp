// Fill out your copyright notice in the Description page of Project Settings.


#include "NetworkedGameModeBase.h"

#include "BasePlayerController.h"
#include "DTR_SpawnableCharacter.h"
#include "GameFramework/PlayerStart.h"
#include "Kismet/GameplayStatics.h"


FString ANetworkedGameModeBase::InitNewPlayer(APlayerController* NewPlayerController, const FUniqueNetIdRepl& UniqueId,
	const FString& Options, const FString& Portal)
{

	APlayerStart* PlayerStart = GetPlayerStartForTeam1();
	if(SpawnedTeam1)
	{
		PlayerStart = GetPlayerStartForTeam2();
	}

	UE_LOG(LogTemp, Warning, TEXT("Picked StartPointNamed: %s"), *PlayerStart->GetName());

	// Spawn An Actor -- Nyax , Drex, Zeher
	UClass* ClassToSpawn = SpawnableCharacters->FindRow<FSpawnableCharacter>("Nyax", "")->PlayableCharacter;
	if(SpawnedTeam1)
	{
		ClassToSpawn = SpawnableCharacters->FindRow<FSpawnableCharacter>("Nyax", "")->PlayableCharacter;
	}

	FVector Location = PlayerStart->GetActorLocation();
	FRotator Rotation = PlayerStart->GetActorRotation();
	FActorSpawnParameters spawnParams;
	spawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	
	ACharacter* SpawnedActor = Cast<ACharacter>(GetWorld()->SpawnActor(ClassToSpawn, &Location, &Rotation, spawnParams));

	NewPlayerController->ClientSetLocation (Location, Rotation);
	
	NewPlayerController->Possess(SpawnedActor);
	SpawnedActor->SetOwner(NewPlayerController);
	Cast<ABasePlayerController>(NewPlayerController)->OnCharacterPossess(SpawnedActor);
	
	SpawnedTeam1 = true;
	
	return Super::InitNewPlayer(NewPlayerController, UniqueId, Options, Portal);
}

APlayerStart* ANetworkedGameModeBase::GetPlayerStartForTeam1()
{
	if(PlayerStarts.Num() == 0)
		CachePlayerStarts();
	
	for(int i = 0; i < PlayerStarts.Num(); ++i)
	{
		if(PlayerStarts[i]->Tags.Contains("Team1"))
		{
			return Cast<APlayerStart>(PlayerStarts[i]);
		}
	}

	return nullptr;}

APlayerStart* ANetworkedGameModeBase::GetPlayerStartForTeam2()
{
	if(PlayerStarts.Num() == 0)
		CachePlayerStarts();
	
	for(int i = 0; i < PlayerStarts.Num(); ++i)
	{
		if(PlayerStarts[i]->Tags.Contains("Team2"))
		{
			return Cast<APlayerStart>(PlayerStarts[i]);
		}
	}

	return nullptr;
}

void ANetworkedGameModeBase::CachePlayerStarts()
{
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerStart::StaticClass(), PlayerStarts);
}
