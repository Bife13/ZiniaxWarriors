// Fill out your copyright notice in the Description page of Project Settings.


#include "SocketConnection.h"

#include "Sockets.h"
#include "SocketSubsystem.h"
#include "Interfaces/IPv4/IPv4Address.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ASocketConnection::ASocketConnection()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASocketConnection::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASocketConnection::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	TArray<uint8> ReceivedData;
	uint32 size = 0;
	int32 Read = 0;
	if (Socket)
	{
		bool HasMessage = Socket->HasPendingData(size);
		if (HasMessage)
		{
			ReceivedData.Init(0, size);
			Socket->Recv(ReceivedData.GetData(), ReceivedData.Num(), Read);
			FString ServerMessage = FString(UTF8_TO_TCHAR(ReceivedData.GetData()));
			GEngine->AddOnScreenDebugMessage(7, 20, FColor::Blue, (TEXT("RECEIVED: '%s'"), *ServerMessage));
			// UNcomment this to Open Game server
			UGameplayStatics::OpenLevel(GetWorld(), *ServerMessage, true);
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(1, 2, FColor::Red, "Nothing");
		}
	}
}

void ASocketConnection::SendConnectInfo()
{
	Socket = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateSocket(NAME_Stream,TEXT("default"), false);
	
	FIPv4Address Ip;

	bool ValidIp = FIPv4Address::Parse(IpString, Ip);
	if(ValidIp)
	{
		const TSharedRef<FInternetAddr> Addr = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateInternetAddr();
		Addr->SetIp(Ip.Value);
		Addr->SetPort(7778);
		const bool connected = Socket->Connect(*Addr);

		if (connected)
		{	
			GEngine->AddOnScreenDebugMessage(1, 5, FColor::Black, "Connected");

			FString FinalString = "";

			FinalString.Append(PlayerName);
			FinalString.Append(PlayerPass);
			FinalString.Append(OptionsString);

			int32 Sent = 0;

			Socket->Send(reinterpret_cast<uint8*>(TCHAR_TO_UTF8(*FinalString)), FinalString.Len(), Sent);
			GEngine->AddOnScreenDebugMessage(2, 5, FColor::Red, "Sent Name");
			// Sent = 0;
			// Socket->Send(reinterpret_cast<uint8*>(TCHAR_TO_UTF8(*PlayerPass)), PlayerPass.Len(), Sent);
			// GEngine->AddOnScreenDebugMessage(3, 5, FColor::Black, "Sent Pass");
			// Sent = 0;
			// Socket->Send(reinterpret_cast<uint8*>(TCHAR_TO_UTF8(*OptionsString)), OptionsString.Len(), Sent);
			// GEngine->AddOnScreenDebugMessage(5, 5, FColor::Black, "Sent Options");
		}
	}
}

void ASocketConnection::StopMatchmaking()
{
	FString Stop = "STOP";
	int32 Sent = 0;
	Socket->Send(reinterpret_cast<uint8*>(TCHAR_TO_UTF8(*Stop)), Stop.Len(), Sent);
}

void ASocketConnection::EndGame()
{
	FString Stop = "END";
	int32 Sent = 0;
	Socket->Send(reinterpret_cast<uint8*>(TCHAR_TO_UTF8(*Stop)), Stop.Len(), Sent);
}

