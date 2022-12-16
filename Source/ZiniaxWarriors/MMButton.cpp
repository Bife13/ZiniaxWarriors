// Fill out your copyright notice in the Description page of Project Settings.


#include "MMButton.h"

UMMButton::UMMButton()
{
	OnClicked.AddDynamic(this, &UMMButton::OnClick);
}

void UMMButton::SetSessionInfo(int sID, TCPClient* tclient)
{
	sessionID = sID;
	tcpClient = tclient;
}

void UMMButton::OnClick()
{
	//tcpClient->JoinGameSession(sessionID);
}
