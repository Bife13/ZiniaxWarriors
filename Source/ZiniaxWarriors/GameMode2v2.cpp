// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode2v2.h"
#include "BasePlayerController.h"
#include "DTR_SkillsDatatable.h"
#include "DTR_SpawnableCharacter.h"
#include "GameState2v2.h"
#include "Sockets.h"
#include "SocketSubsystem.h"
#include "GameFramework/PlayerStart.h"
#include "GameFramework/SpringArmComponent.h"
#include "Interfaces/IPv4/IPv4Address.h"
#include "Kismet/GameplayStatics.h"



void AGameMode2v2::BeginPlay()
{
	Super::BeginPlay();
	Socket = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateSocket(NAME_Stream,TEXT("default"), false);

	if(!OptionsString.IsEmpty())
	{
		IpString = UGameplayStatics::ParseOption(OptionsString, "IP");
		PlayerName = IpString;
		PlayerName.Append(":");
		PlayerName.Append(FString::FromInt(GetWorld()->URL.Port));
		PlayerName.Append("|");
	}
	
	FIPv4Address Ip;

	bool ValidIp = FIPv4Address::Parse(IpString, Ip);
	if (ValidIp)
	{
		const TSharedRef<FInternetAddr> Addr = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateInternetAddr();
		Addr->SetIp(Ip.Value);
		Addr->SetPort(7778);
		const bool connected = Socket->Connect(*Addr);

		if (connected)
		{
			UE_LOG(LogTemp, Warning, TEXT("Server Connected To Matchmaking"));

			GEngine->AddOnScreenDebugMessage(1, 5, FColor::Black, "Connected");

			FString FinalString = "";

			FinalString.Append(PlayerName);
			FinalString.Append(PlayerPass);
			//FinalString.Append(OptionsString);

			int32 Sent = 0;

			Socket->Send(reinterpret_cast<uint8*>(TCHAR_TO_UTF8(*FinalString)), FinalString.Len(), Sent);
			GEngine->AddOnScreenDebugMessage(2, 5, FColor::Red, "Sent Name");
			Sent = 0;
			// Socket->Send(reinterpret_cast<uint8*>(TCHAR_TO_UTF8(*PlayerPass)), PlayerPass.Len(), Sent);
			// GEngine->AddOnScreenDebugMessage(3, 5, FColor::Black, "Sent Pass");
			// Sent = 0;
			// Socket->Send(reinterpret_cast<uint8*>(TCHAR_TO_UTF8(*OptionsString)), OptionsString.Len(), Sent);
			// GEngine->AddOnScreenDebugMessage(5, 5, FColor::Black, "Sent Options");

			GameState2v2 = GetWorld()->GetGameState<AGameState2v2>();
			UpdateRoundsInGameState();
		}else
		{
			UE_LOG(LogTemp, Warning, TEXT("Server Not connected to Matchmaking"));

		}
	}
}

FString AGameMode2v2::InitNewPlayer(APlayerController* NewPlayerController, const FUniqueNetIdRepl& UniqueId,
                                    const FString& Options, const FString& Portal)
{
	// TODO if need to go back to old method, just override the Variables
	FString TestOptions = "?Warrior=Zerher?Ability1=Roar?Ability2=SniperShot?Ability3=EletroGate";

	if (Options.Len() > 0)
	{
		TestOptions = Options;
	}
	FString Warrior = ParsingWarriorName(TestOptions);
	FString Ability1 = ParsingAbility1(TestOptions);
	FString Ability2 = ParsingAbility2(TestOptions);
	FString Ability3 = ParsingAbility3(TestOptions);
	
	


	APlayerStart* PlayerStart = GetPlayerStartsForTeam1()[CurrentStart];
	if (SpawnedPlayer)
	{
		PlayerStart = GetPlayerStartsForTeam2()[CurrentStart];
	}


	UE_LOG(LogTemp, Warning, TEXT("Picked StartPointNamed: %s"), *PlayerStart->GetName());

	TArray<FName> CharacterNames = {"Nyax", "Drex", "Zerher"};

	// Spawn An Actor												// Nyax, Drex, Zerher

	int CharIndex = FMath::RandRange(0, 2);
	UClass* ClassToSpawn = SpawnableCharacters->FindRow<FSpawnableCharacter>(FName(Warrior), "")->
	                                            PlayableCharacter;
	if (SpawnedPlayer)
	{
		ClassToSpawn = SpawnableCharacters->FindRow<FSpawnableCharacter>(FName(Warrior), "")->
		                                    PlayableCharacter;
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

	TSubclassOf<USkillBase> SetAbility1 = SkillsDatatable->FindRow<FSkillsDatatable>(FName(Ability1), "")->Skill;
	TSubclassOf<USkillBase> SetAbility2 = SkillsDatatable->FindRow<FSkillsDatatable>(FName(Ability2), "")->Skill;
	TSubclassOf<USkillBase> SetAbility3 = SkillsDatatable->FindRow<FSkillsDatatable>(FName(Ability3), "")->Skill;

	PlayableCharacter->SetSkills(SetAbility1, SetAbility2, SetAbility3);

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

	FString Filename = "C:/Users/skyzf/Documents/Unreal Projects/ZiniaxWarriorsBuild/Stats/Stats.txt";
	bool PrintedWarrior = FFileHelper::SaveStringToFile("Warrior: " + Warrior + "\r\n", *Filename,
	                                                    FFileHelper::EEncodingOptions::AutoDetect,
	                                                    &IFileManager::Get(), EFileWrite::FILEWRITE_Append);
	bool PrintedAbility1 = FFileHelper::SaveStringToFile("Ability1: " + Ability1 + "\r\n", *Filename,
	                                                     FFileHelper::EEncodingOptions::AutoDetect,
	                                                     &IFileManager::Get(), EFileWrite::FILEWRITE_Append);
	bool PrintedAbility2 = FFileHelper::SaveStringToFile("Ability2: " + Ability2 + "\r\n", *Filename,
	                                                     FFileHelper::EEncodingOptions::AutoDetect,
	                                                     &IFileManager::Get(), EFileWrite::FILEWRITE_Append);
	bool PrintedAbility3 = FFileHelper::SaveStringToFile("Ability3: " + Ability3 + "\r\n", *Filename,
	                                                     FFileHelper::EEncodingOptions::AutoDetect,
	                                                     &IFileManager::Get(), EFileWrite::FILEWRITE_Append);

	return Super::InitNewPlayer(NewPlayerController, UniqueId, Options, Portal);
}

void AGameMode2v2::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (bCanDoorOpen)
	{
		OpenDoors(DeltaSeconds);
	}

	MatchTimer();
}

bool AGameMode2v2::ReadyToStartMatch_Implementation()
{
	if (GetMatchState() == MatchState::WaitingToStart)
	{
		if (SpawnDoors.Num() == 0)
		{
			CacheDoors();
		}
		if (PlayerCounter >= MaxPlayers)
		{
			SetDeathEvents();
			StartInBetweenRoundTimer(DelayBetweenRounds);
			StartMatchMusicEvent();
			return true;
		}
	}
	return false;
}

FString AGameMode2v2::ParsingWarriorName(const FString& Options)
{
	return UGameplayStatics::ParseOption(Options, "Warrior");
}

FString AGameMode2v2::ParsingAbility1(const FString& Options)
{
	return UGameplayStatics::ParseOption(Options, "Ability1");
}

FString AGameMode2v2::ParsingAbility2(const FString& Options)
{
	return UGameplayStatics::ParseOption(Options, "Ability2");
}

FString AGameMode2v2::ParsingAbility3(const FString& Options)
{
	return UGameplayStatics::ParseOption(Options, "Ability3");
}

void AGameMode2v2::StartInBetweenRoundTimer(float Time)
{
	FTimerHandle UnusedHandle;
	GetWorldTimerManager().SetTimer(
		UnusedHandle, this, &AGameMode2v2::ActivateAllCharacters, Time, false);
}

void AGameMode2v2::StartDoorTimer(float Time)
{
	FTimerHandle UnusedHandle;
	GetWorldTimerManager().SetTimer(
		UnusedHandle, this, &AGameMode2v2::SetCanDoorOpenTrue, Time, false);
}

void AGameMode2v2::RestartGameAfterDelay(float Time)
{
	FTimerHandle UnusedHandle;
	GetWorldTimerManager().SetTimer(
		UnusedHandle, this, &AGameMode2v2::SendPlayersToLogin, Time, false);
}

void AGameMode2v2::RespawnAfterDelay(float Time)
{
    FTimerHandle UnusedHandle;
    GetWorldTimerManager().SetTimer(
        UnusedHandle, this, &AGameMode2v2::RespawnCharacters, Time, false);
}

void AGameMode2v2::RestartServerAfterDelay(float Time)
{
	FTimerHandle UnusedHandle;
	GetWorldTimerManager().SetTimer(
		UnusedHandle, this, &AGameMode2v2::RestartServer, Time, false);
}

void AGameMode2v2::ActivateAllCharacters()
{
	for (int i = 0; i < PlayerControllers.Num(); i++)
	{
		PlayerControllers[i]->CharacterActivate();
	}
	for (int i = 0; i < Team1PlayerCharacters.Num(); i++)
	{
		Team1PlayerCharacters[i]->PlayCatchphrase();
		Team2PlayerCharacters[i]->PlayCatchphrase();
	}
	
	StartDoorTimer(5);
}

void AGameMode2v2::DeactivateAllCharacters()
{
	for (int i = 0; i < PlayerControllers.Num(); i++)
	{
		PlayerControllers[i]->CharacterDeactivate();
	}

	CloseDoors();
}

void AGameMode2v2::CloseDoors()
{
	for (int i = 0; i < SpawnDoors.Num(); i++)
	{
		FVector Location = SpawnDoors[i]->GetActorLocation();
		FVector MoveVector = {0, 0, 200};
		FVector FinalPosition = Location + MoveVector;
		SpawnDoors[i]->SetActorLocation(FinalPosition);
	}
}

void AGameMode2v2::SetMinutesInGameState()
{
	GameState2v2->SetMinutes(Minutes);
}

void AGameMode2v2::SetSecondsInGameState()
{
	GameState2v2->SetSeconds(Seconds);
}

void AGameMode2v2::SetRoundCountInGameState()
{
	UE_LOG(LogTemp, Warning, TEXT("RoundNumber: %d"), RoundCounter);
	GameState2v2->SetRounds(RoundCounter);
}

void AGameMode2v2::SetTeam1RoundsWonInGameState()
{
	UE_LOG(LogTemp, Warning, TEXT("Teeam1 won: %d"), Team1RoundsWon);
	GameState2v2->SetTeam1Rounds(Team1RoundsWon);
}

void AGameMode2v2::SetTeam2RoundsWonInGameState()
{
	UE_LOG(LogTemp, Warning, TEXT("Teeam2 won: %d"), Team2RoundsWon);
	GameState2v2->SetTeam2Rounds(Team2RoundsWon);
}


void AGameMode2v2::UpdateRoundsInGameState()
{
	GameState2v2->SetAllRounds(RoundCounter, Team1RoundsWon, Team2RoundsWon);
	GameState2v2->ScoreUpdate.Broadcast(RoundCounter, Team1RoundsWon, Team2RoundsWon);
}

void AGameMode2v2::UpdateGameTimer()
{
	SetMinutesInGameState();
	SetSecondsInGameState();
}

void AGameMode2v2::OpenDoors(float DeltaTime)
{
	
	for (int i = 0; i < SpawnDoors.Num(); i++)
	{
		FVector Location = SpawnDoors[i]->GetActorLocation();
		FVector Vector = {0, 0, 200};
		SpawnDoors[i]->SetActorLocation(FMath::VInterpTo(Location, Location - Vector, DeltaTime,
		                                                 0.6f));
		if (Location.Z <= 15)
		{
			SetCanDoorOpenFalse();
		}
	}

	for(int i = 0; i < Team1PlayerCharacters.Num(); i++)
	{
		Team1PlayerCharacters[i]->CallRoundStartSound();
	}

	for(int i = 0; i < Team2PlayerCharacters.Num(); i++)
	{
		Team2PlayerCharacters[i]->CallRoundStartSound();
	}
}


void AGameMode2v2::SetDeathEvents()
{
	if (!bIsGameStarted && PlayerCounter >= MaxPlayers)
	{
		bIsGameStarted = true;
		for (int i = 0; i < Team1HealthComponents.Num(); i++)
		{
			if (Team1HealthComponents[i])
				Team1HealthComponents[i]->OnDeathEvent.AddUFunction(this, "CountDeath", 1,
				                                                    Team1PlayerCharacters[i]->GetController(),
				                                                    Team1PlayerCharacters[i]);
		}

		for (int i = 0; i < Team2HealthComponents.Num(); i++)
		{
			if (Team2HealthComponents[i])
				Team2HealthComponents[i]->OnDeathEvent.AddUFunction(this, "CountDeath", 2,
				                                                    Team2PlayerCharacters[i]->GetController(),
				                                                    Team2PlayerCharacters[i]);
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
		Team1PlayerCharacters[i]->PlayCatchphrase();
		Team1PlayerCharacters[i]->ResetMesh();
		Team1PlayerCharacters[i]->SetIsDead(false);
	}

	for (int i = 0; i < Team2PlayerCharacters.Num(); i++)
	{
		Team2PlayerCharacters[i]->SetActorLocation(GetPlayerStartsForTeam2()[i]->GetActorLocation());
		Team2PlayerCharacters[i]->ResetCharacter();
		Team2PlayerCharacters[i]->PlayCatchphrase();
		Team2PlayerCharacters[i]->ResetMesh();
		Team2PlayerCharacters[i]->SetIsDead(false);
	}
}

void AGameMode2v2::CountDeath(int TeamId, ABasePlayerController* DeadCharacterController,
                              APlayableCharacter* DeadCharacter)
{
	if (TeamId == 1)
	{
		Team1DeathCounter++;
		DeadCharacterController->CharacterDeactivate();
		DeadCharacter->SetIsDead(true);
	}
	else
	{
		Team2DeathCounter++;
		DeadCharacterController->CharacterDeactivate();
		DeadCharacter->SetIsDead(true);
	}

	if (Team1DeathCounter >= Team1PlayerCharacters.Num() || Team2DeathCounter >= Team2PlayerCharacters.Num())
	{
		RoundCounter++;
		if (Team1DeathCounter >= Team1PlayerCharacters.Num())
		{
			Team2RoundsWon++;
			if (Team1RoundsWon < 3 && Team2RoundsWon < 3)
			{
				for(int i = 0; i < Team1PlayerCharacters.Num(); i++)
				{
					Team1PlayerCharacters[i]->CallDefeatSound();
				}

				for(int i = 0; i < Team2PlayerCharacters.Num(); i++)
				{
					Team2PlayerCharacters[i]->CallVictorySound();
				}
			}
		

		}
		else if (Team2DeathCounter >= Team2PlayerCharacters.Num())
		{
			Team1RoundsWon++;
			if (Team1RoundsWon < 3 && Team2RoundsWon < 3)
			{
				for(int i = 0; i < Team2PlayerCharacters.Num(); i++)
				{
					Team2PlayerCharacters[i]->CallDefeatSound();
				}

				for(int i = 0; i < Team1PlayerCharacters.Num(); i++)
				{
					Team1PlayerCharacters[i]->CallVictorySound();
				}
			}
		}
		
		if (!CheckRoundCounter())
		{
			StartInBetweenRoundTimer(DelayAfterRoundEnd+ DelayBetweenRounds);
			Team1DeathCounter = Team2DeathCounter = 0;
		}
		UpdateRoundsInGameState();
		RespawnAfterDelay(DelayAfterRoundEnd);
	}
}

bool AGameMode2v2::CheckRoundCounter()
{
	// TODO WAit a bit before ending Game

	FString EndString = "END";
	if (Team1RoundsWon >= 3)
	{
		GEngine->AddOnScreenDebugMessage(1, 2, FColor::Black, "Team 1 Won");
		int32 Sent = 0;
		Socket->Send(reinterpret_cast<uint8*>(TCHAR_TO_UTF8(*EndString)), EndString.Len(), Sent);
		RestartGameAfterDelay(DelayAfterGameEnd);
		for(int i = 0; i < Team1PlayerCharacters.Num(); i++)
		{
			Team1PlayerCharacters[i]->AnnounceVictory();
		}

		for(int i = 0; i < Team2PlayerCharacters.Num(); i++)
		{
			Team2PlayerCharacters[i]->AnnounceDefeat();
		}
		return true;
	}
	if (Team2RoundsWon >= 3)
	{
		GEngine->AddOnScreenDebugMessage(1, 2, FColor::Black, "Team 2 Won");
		int32 Sent = 0;
		Socket->Send(reinterpret_cast<uint8*>(TCHAR_TO_UTF8(*EndString)), EndString.Len(), Sent);
		RestartGameAfterDelay(DelayAfterGameEnd);
		for(int i = 0; i < Team2PlayerCharacters.Num(); i++)
		{
			Team2PlayerCharacters[i]->AnnounceVictory();
		}

		for(int i = 0; i < Team1PlayerCharacters.Num(); i++)
		{
			Team1PlayerCharacters[i]->AnnounceDefeat();
		}
		return true;
	}
	return false;
}

void AGameMode2v2::SendPlayersToLogin()
{
	for (int i = 0; i < PlayerControllers.Num(); i++)
	{
		PlayerControllers[i]->ReopenLogin();
	}
	RestartServerAfterDelay(1);
}

void AGameMode2v2::RestartServer()
{
	RestartGame();
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

void AGameMode2v2::CacheDoors()
{
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), "Door", SpawnDoors);
}
