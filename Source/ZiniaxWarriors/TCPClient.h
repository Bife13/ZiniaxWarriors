// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ZWConnectPlayerState.h"

/**
 * 
 */
class ZINIAXWARRIORS_API TCPClient: public FRunnable
{
public:
	
	TCPClient(AZWConnectPlayerState* pState);
	TCPClient();
	TCPClient(FString MMIP);
	bool isClient;
	~TCPClient();
	virtual bool Init() override;
	virtual uint32 Run() override;
	void SaveServerIP(FString tosave);
	void ConnectPlayerToGame(FString ConfigStr);
	void SendPlayerPass(FString name, FString pass);
	void SendPlayerLogin(FString name, FString pass);
	void SendLoginToServer(FString MessageToSend);
	virtual void Stop() override;  

	void SendMessageToServer(FString MessageToSend);

	bool saveIp=false;

	void SendGameServerInfo(FString host, FString port);
	bool IsConnected();

	
	FString getGameIP(){return  GameServerToConnect;}
	
	private:
	FString GameServerToConnect;
	FIPv4Address serverIP;
	FRunnableThread* Thread;
	FSocket* Socket;
	FSocket* ListenerSocket;
	bool running;
	bool connected;
	class AZWConnectPlayerState* PlayerState;
};
