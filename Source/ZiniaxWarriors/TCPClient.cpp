// Fill out your copyright notice in the Description page of Project Settings.


#include "TCPClient.h"

#include <string>

#include "Sockets.h"
#include "SocketSubsystem.h"
#include "Interfaces/IPv4/IPv4Address.h"


TCPClient::TCPClient(AZWConnectPlayerState* pState)
{
	PlayerState = pState;
	serverIP = PlayerState->MatchmakingIP;
	Thread = FRunnableThread::Create(this, TEXT("TCPClientThread"),
									0,  TPri_Normal);
		

}


TCPClient::~TCPClient()
{
	
	Stop();
	delete Thread;
}
void TCPClient::Stop()
{
	UE_LOG(LogTemp, Log, TEXT("Thread Done!"));
	running = false;
}



bool TCPClient::Init()
{
	
	Socket = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)
	->CreateSocket(NAME_Stream, TEXT("default"), false);
	int32 NewSize = 0;
	Socket->SetReceiveBufferSize(1024, NewSize);
	FIPv4Address matchmakingServerIP(serverIP.Value);
	TSharedRef<FInternetAddr> matchmakingServer = ISocketSubsystem::Get(
												PLATFORM_SOCKETSUBSYSTEM)->CreateInternetAddr();
	matchmakingServer->SetIp(matchmakingServerIP.Value);
	matchmakingServer->SetPort(8888);
	
	connected = Socket->Connect(*matchmakingServer);
	if (connected)  {
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow,FString::Printf(TEXT("Connected!")));
		UE_LOG(LogTemp, Log, TEXT("CONNECTED!"));
	}
		
	return 0;
}



uint32 TCPClient::Run()
{
	running = true;
	TArray<uint8> ReceivedData;
	while (running)
	{
		uint32 Size = 0;
		if (Socket->HasPendingData(Size))
		{
			ReceivedData.Init(0, Size);
			int32 Read = 0;
			Socket->Recv(ReceivedData.GetData(), ReceivedData.Num(), Read);
			FString ServerMessage = FString(UTF8_TO_TCHAR(  ReceivedData.GetData()));
			UE_LOG(LogTemp, Log, TEXT("RECEIVED: '%s'"), *ServerMessage);

			//RunCode of Player State Here if ServerMessage[0] is something
			if(ServerMessage.Compare("SendLogin")==0)
			{
				UE_LOG(LogTemp, Log, TEXT("SendingLogin"));
				SendMessageToServer(PlayerState->ClientName);
			}

			if(ServerMessage.Compare("SendName")==0)
			{
				
				UE_LOG(LogTemp, Log, TEXT("SendingName"));
				SendMessageToServer(PlayerState->ClientName);
			}
			
			if ((ServerMessage[0] == 's') && (PlayerState))
			{
				//PlayerState->UpdateSessionsList(ServerMessage);
			}
			else if ((ServerMessage[0] == 'o') && (PlayerState))
			{
				TArray<FString> Out;
				ServerMessage.ParseIntoArray(Out, TEXT("|"), true);
				FSessionInfo session;
				session.id = -1;
				session.name = "";
				session.serverip = Out[1];
				session.serverport = FCString::Atoi(*Out[2]);
				PlayerState->ConnectToGameServer(session);
			}
		}
	}
	return 0;
}

void TCPClient::ConnectPlayerToGame(FString ConfigStr)
{
	FString Command = "/SaveConfig.";
	UE_LOG(LogTemp, Log, TEXT("name in Thread: '%s'"),*Command);

	TCHAR *serializedCharCommand =	(Command).GetCharArray().GetData();
	int32 sizeCommand = FCString::Strlen(serializedCharCommand);
	int32 sentCommand = 0;
	bool successfulCommand = Socket->Send((uint8*)  TCHAR_TO_UTF8(serializedCharCommand), sizeCommand, sentCommand);
	if (successfulCommand)
	{

		FString temp = ConfigStr + '.';
		UE_LOG(LogTemp, Log, TEXT("name in Thread: '%s'"),*temp);

		TCHAR *serializedChar =	(temp).GetCharArray().GetData();
		int32 size = FCString::Strlen(serializedChar);
		int32 sent = 0;
		bool successful = Socket->Send((uint8*)  TCHAR_TO_UTF8(serializedChar), size, sent);
		if (successful)
		{
			UE_LOG(LogTemp, Log, TEXT("Sent my config to server!!!"));
		}
	}
	
	
}

void TCPClient::SendPlayerLogin(FString name, FString pass)
{
	UE_LOG(LogTemp, Log, TEXT("Sending Login"));
	FString temp = name + '.';
	UE_LOG(LogTemp, Log, TEXT("name in Thread: '%s'"),*temp);
	TCHAR *serializedChar =	(temp).GetCharArray().GetData();
	int32 size = FCString::Strlen(serializedChar);
	int32 sent = 0;
	bool successful = Socket->Send((uint8*)  TCHAR_TO_UTF8(serializedChar), size, sent);
	if (successful)
	{
		UE_LOG(LogTemp, Log, TEXT("Client name SENT!!!!"));
		FString temp2 = pass + '.';
		UE_LOG(LogTemp, Log, TEXT("Pass in Thread: '%s'"),*temp2);
		TCHAR *serializedCharPass =	(temp2).GetCharArray().GetData();
		int32 sizeP = FCString::Strlen(serializedCharPass);
		int32 sentP = 0;
		bool successfulP = Socket->Send((uint8*)  TCHAR_TO_UTF8(serializedCharPass), sizeP, sentP);
		if (successfulP)
		{
			UE_LOG(LogTemp, Log, TEXT("Client Pass SENT!!!!"));
			PlayerState->ShowCustomizationMenu();
		}
	}
}



void TCPClient::SendLoginToServer(FString MessageToSend)
{
	MessageToSend+='.';
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow,FString::Printf(TEXT("%s"),*MessageToSend));
	
	TCHAR *serializedChar = MessageToSend.GetCharArray().GetData();
	int32 size = FCString::Strlen(serializedChar);
	int32 sent = 0;
	bool successful = Socket->Send((uint8*)  TCHAR_TO_UTF8(serializedChar), size, sent);
	if (successful)
	{
		UE_LOG(LogTemp, Log, TEXT("MESSAGE SENT!!!!"));
	}
}


void TCPClient::CreateNewGameSession(FString sname)
{
	FString serialized = "c|" + sname + "|#";
	//turn FString into Char[]
	TCHAR *serializedChar = serialized.GetCharArray().GetData();
	int32 size = FCString::Strlen(serializedChar);
	int32 sent = 0;
	bool successful = Socket->Send((uint8*)  TCHAR_TO_UTF8(serializedChar), size, sent);
	if (successful)
	{
		UE_LOG(LogTemp, Log, TEXT("MESSAGE SENT!!!!"));
	}


	
}







void TCPClient::SendPlayerNameCommand()
{
	FString serialized = "/setName.";
	TCHAR *serializedChar = serialized.GetCharArray().GetData();
	int32 size = FCString::Strlen(serializedChar);
	int32 sent = 0;
	bool successful = Socket->Send((uint8*)  TCHAR_TO_UTF8(serializedChar), size, sent);
	if (successful)
	{
		UE_LOG(LogTemp, Log, TEXT("MESSAGE SENT!!!!"));
	}
	
	
}

void TCPClient::SendMessageToServer( FString MessageToSend)
{
	MessageToSend+='.';
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow,FString::Printf(TEXT("%s"),*MessageToSend));
	
	TCHAR *serializedChar = MessageToSend.GetCharArray().GetData();
	int32 size = FCString::Strlen(serializedChar);
	int32 sent = 0;
	bool successful = Socket->Send((uint8*)  TCHAR_TO_UTF8(serializedChar), size, sent);
	if (successful)
	{
		UE_LOG(LogTemp, Log, TEXT("MESSAGE SENT!!!!"));
	}
}


void TCPClient::JoinGameSession(int sID)
{
	FString serialized = "j|" + FString::FromInt(sID) + "|#";
	TCHAR *serializedChar = serialized.GetCharArray().GetData();
	int32 size = FCString::Strlen(serializedChar);
	int32 sent = 0;
	bool successful = Socket->Send((uint8*)  TCHAR_TO_UTF8(serializedChar), size, sent);
	if (successful)
	{
		UE_LOG(LogTemp, Log, TEXT("MESSAGE SENT!!!!"));
	}
		
}

bool TCPClient::IsConnected()
{
	return connected;
}
