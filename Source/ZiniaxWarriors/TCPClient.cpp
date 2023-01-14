// Fill out your copyright notice in the Description page of Project Settings.


#include "TCPClient.h"

#include <concrt.h>
#include <string>

#include "Sockets.h"
#include "SocketSubsystem.h"
#include "Interfaces/IPv4/IPv4Address.h"


// player connecting via UI  
TCPClient::TCPClient(AZWConnectPlayerState* pState)
{
	UE_LOG(LogTemp, Log, TEXT("I AM CLIENT Thread!"));
	PlayerState = pState;
	serverIP = PlayerState->MatchmakingIP;
	isClient = true;
	GameServerToConnect.Reset();
	Thread = FRunnableThread::Create(this, TEXT("TCPClientThread"),
									0,  TPri_Normal);
	
}

// Game Server try connect to same machine Macth making serverserver 
TCPClient::TCPClient()
{
	UE_LOG(LogTemp, Log, TEXT("I AM Server Thread!"));
	serverIP = FIPv4Address(127,0,0,1);
	isClient = false;
	Thread = FRunnableThread::Create(this, TEXT("TCPClientThread"),
									0,  TPri_Normal);
}

TCPClient::TCPClient(FString MMIP)
{
	FIPv4Address tosend ;
	if(FIPv4Address::Parse(MMIP,tosend))
	{
		UE_LOG(LogTemp, Log, TEXT("I AM Server Thread!"));
		serverIP = tosend;
		isClient = false;
		Thread = FRunnableThread::Create(this, TEXT("TCPClientThread"),
										0,  TPri_Normal);
	}
	else
	{
		UE_LOG(LogTemp,Log, TEXT("Invalid Matchmaking Ip Input"));
		
	}
	
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


//on creating class
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
		UE_LOG(LogTemp, Log, TEXT("Match making CONNECTED!"));
		return true;
	}
		
	return false;
}



uint32 TCPClient::Run()
{
	running = true;
	TArray<uint8> ReceivedData;
	while (running)
	{
		//UE_LOG(LogTemp, Log, TEXT("Waiting for message"),);
		uint32 Size = 0;
		if (Socket->HasPendingData(Size))
		{
			ReceivedData.Init(0, Size);
			int32 Read = 0;
			Socket->Recv(ReceivedData.GetData(), ReceivedData.Num(), Read);
			FString ServerMessage = FString(UTF8_TO_TCHAR(  ReceivedData.GetData()));
			UE_LOG(LogTemp, Log, TEXT("RECEIVED: '%s'"), *ServerMessage);

			if(ServerMessage.Compare("GameServerReady")==0)
			{
				//PlayerState->UpdateCanvas();
				UE_LOG(LogTemp, Log, TEXT("Go to level via ip"));
				
				PlayerState->GotoGameLevel();
			}

			if(ServerMessage.Compare("GameServerWaiting")==0)
			{
				PlayerState->UpdateCanvas();
			}

			if(saveIp &&GameServerToConnect.IsEmpty())
			{
				saveIp= false;
				SaveServerIP(ServerMessage);
			}
				
			if(ServerMessage.Compare("IP")==0 && saveIp ==false)
			{
				saveIp = true;
			}

			
			//RunCode of Player State Here if ServerMessage[0] is something
		
			/*
			if(isClient)
			{
				UE_LOG(LogTemp, Log, TEXT("CLIENT RECEIVED: '%s'"), *ServerMessage);
				//TODO game CLIENT   Handle messages from matchmaking server
				//
				
				
				
				
			}
			else
			{
				//TODO game SERVER Handle messages from matchmaking server
				UE_LOG(LogTemp, Log, TEXT(" Server RECEIVED: '%s'"), *ServerMessage);

				
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
			*/
		}
	}
	return 0;
}

#pragma  region PlayerConnections

void TCPClient::SaveServerIP(FString tosave)
{
	UE_LOG(LogTemp, Log, TEXT("Got ip for Game '%s'"),*tosave);
	GameServerToConnect = tosave;
	UE_LOG(LogTemp, Log, TEXT("Saved ip for Game '%s'"),*GameServerToConnect);
	saveIp= false;
	
};

void TCPClient::ConnectPlayerToGame(FString ConfigStr)
{

	if(!PlayerState->ClientWaitingforGame)
	{
		UE_LOG(LogTemp, Log, TEXT("Sent my config to server!!!"));
		FString tempL = "/join.";
		UE_LOG(LogTemp, Log, TEXT("Command in Thread: '%s'"),*tempL);

		TCHAR *serializedCharL =	(tempL).GetCharArray().GetData();
		int32 sizeL = FCString::Strlen(serializedCharL);
		int32 sentL = 0; 
		bool successfulL = Socket->Send((uint8*)  TCHAR_TO_UTF8(serializedCharL), sizeL, sentL);
		if (successfulL)
		{
			UE_LOG(LogTemp, Log, TEXT("Matchmaking is oky!!!"));
			PlayerState->WaitingForGame(true);
			//this->Run();
			//running=true;
			/*
			FString Command = "/SaveConfig.";
			UE_LOG(LogTemp, Log, TEXT("name in Thread: '%s'"),*Command);

			TCHAR *serializedCharCommand =	(Command).GetCharArray().GetData();
			int32 sizeCommand = FCString::Strlen(serializedCharCommand);
			int32 sentCommand = 0;
			bool successfulCommand = Socket->Send((uint8*)  TCHAR_TO_UTF8(serializedCharCommand), sizeCommand, sentCommand);
			if (successfulCommand)
			{

				FString temp = ConfigStr + ".\0";
				UE_LOG(LogTemp, Log, TEXT("Config in Thread: '%s'"),*temp);

				TCHAR *serializedChar =	(temp).GetCharArray().GetData();
				int32 size = FCString::Strlen(serializedChar);
				int32 sent = 0;
				bool successful = Socket->Send((uint8*)  TCHAR_TO_UTF8(serializedChar), size, sent);
				if (successful)
				{
				
			
				}
			}

			*/
		}
		
	}
	else
	{
		FString Command = "/cancel.";
		UE_LOG(LogTemp, Log, TEXT("Command in Thread: '%s'"),*Command);

		TCHAR *serializedCharCommand =	(Command).GetCharArray().GetData();
		int32 sizeCommand = FCString::Strlen(serializedCharCommand);
		int32 sentCommand = 0;
		bool successfulCommand = Socket->Send((uint8*)  TCHAR_TO_UTF8(serializedCharCommand), sizeCommand, sentCommand);
		if (successfulCommand)
		{
			UE_LOG(LogTemp, Log, TEXT("'%s'ed Matchmaking"),*Command);
			PlayerState->WaitingForGame(false);
		}


		
	}
	
	
	
}

void TCPClient::SendPlayerPass(FString name, FString pass)
{

	
}




void TCPClient::SendPlayerLogin(FString name, FString pass)
{
	UE_LOG(LogTemp, Log, TEXT("Sending client"));
	FString tempC = "/client.\0";
	UE_LOG(LogTemp, Log, TEXT("name in Thread: '%s'"),*tempC);
	TCHAR *serializedCharC =	(tempC).GetCharArray().GetData();
	int32 sizeC = FCString::Strlen(serializedCharC);
	int32 sentC = 0;
	bool successfulC = Socket->Send((uint8*)  TCHAR_TO_UTF8(serializedCharC), sizeC, sentC);
	if (successfulC)
	{
		UE_LOG(LogTemp, Log, TEXT("Sending Name"));
		FString temp = name + ".\0";
		UE_LOG(LogTemp, Log, TEXT("name in Thread: '%s'"),*temp);
		TCHAR *serializedChar =	(temp).GetCharArray().GetData();
		int32 size = FCString::Strlen(serializedChar);
		int32 sent = 0;
		bool successful = Socket->Send((uint8*)  TCHAR_TO_UTF8(serializedChar), size, sent);
		if (successful)
		{
			
			//Concurrency::wait(1000);
			UE_LOG(LogTemp, Log, TEXT("Client name SENT!!!!"));
			//SendPass:
			FString temp2 = pass + ".\0";
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
			else{
				GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow,FString::Printf(TEXT("Unable to Connect!")));
		
			}
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow,FString::Printf(TEXT("Unable to Connect!")));
		
		}
	}

	
}
#pragma endregion 


/*
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
*/


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

void TCPClient::SendGameServerInfo(FString host,FString port)
{
	FString serialized = "/gameserver.";
	TCHAR *serializedChar = serialized.GetCharArray().GetData();
	int32 size = FCString::Strlen(serializedChar);
	int32 sent = 0;
	bool successful = Socket->Send((uint8*)  TCHAR_TO_UTF8(serializedChar), size, sent);
	if (successful)
	{
		//send port
		FString serializedHost = port+'.';
		UE_LOG(LogTemp, Log, TEXT("Sending port: '%s'"), *serializedHost);
		TCHAR *serializedCharHost = serializedHost.GetCharArray().GetData();
		int32 sizeHost = FCString::Strlen(serializedCharHost);
		int32 sentHost = 0;
		bool successfulHost = Socket->Send((uint8*)  TCHAR_TO_UTF8(serializedCharHost), sizeHost, sentHost);
		if (successfulHost)
		{
			UE_LOG(LogTemp, Log, TEXT("IP MESSAGE SENT!!!!"));
			this->Stop();
				
		}
	}
}





bool TCPClient::IsConnected()
{
	return connected;
}
