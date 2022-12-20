// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Runtime/Networking/Public/Networking.h"
#include "Networking/Public/Common/TcpListener.h"
//#include "Interfaces/IPv4/IPv4Endpoint.h"
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ZWSocketManager.generated.h"


DECLARE_DELEGATE_RetVal_OneParam(bool, FGetGameServerAnswer, FString)
class FTcpListener;
/**
 * 
 */
UCLASS()
class ZINIAXWARRIORS_API UZWSocketManager : public UObject
{
	GENERATED_BODY()
public:
	/*
	 *
	
	UZWSocketManager();

	virtual ~UZWSocketManager() override;

	
	void SendRegisterServer();

	void SendGetGameServer();
	
	FGetGameServerAnswer& GetServerIpDelegate();


private:
	FGetGameServerAnswer ServerIpDelegate;
	
	bool FormatIP4ToNumber(const FString& TheIP, uint8 (&Out)[4]);
    
	FString StringFromBinaryArray(TArray<uint8> BinaryArray);
    
	FSocket* ListenerSocket;
	FSocket* SendSocket;
    
	FTcpListener* SocketListener;
    
	bool NotificationReceived(FSocket* InSocket, const FIPv4Endpoint& ClientEndPoint);
	void StartNotificationChecks();

	FString ReadServerIpFromCommandline();

	FString ReadMatchmakingServerIpFromCommandline();
	FString ReadMatchmakingServerPortFromCommandline();
	*/
};
