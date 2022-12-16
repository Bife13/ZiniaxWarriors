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
	bool isClient;
	~TCPClient();
	virtual bool Init() override;
	virtual uint32 Run() override;
	void ConnectPlayerToGame(FString ConfigStr);
	void SendPlayerLogin(FString name, FString pass);
	void SendLoginToServer(FString MessageToSend);
	virtual void Stop() override;  
	void CreateNewGameSession(FString sname);
	void SendPlayerNameCommand();
	void SendMessageToServer(FString MessageToSend);
	
	void JoinGameSession(int sID);
	bool IsConnected();
	
	private:
	FIPv4Address serverIP;
	FRunnableThread* Thread;
	FSocket* Socket;
	FSocket* ListenerSocket;
	bool running;
	bool connected;
	class AZWConnectPlayerState* PlayerState;
};
