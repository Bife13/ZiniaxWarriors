// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TCPClient.h"
#include "Components/Button.h"
#include "MMButton.generated.h"

/**
 * 
 */
UCLASS()
class ZINIAXWARRIORS_API UMMButton : public UButton
{
	GENERATED_BODY()
public:
	UMMButton();
	void SetSessionInfo(int sID, TCPClient *tclient);
	protected:
	int sessionID;
	TCPClient *tcpClient;
	UFUNCTION()
	void OnClick();
};
