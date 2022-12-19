// Fill out your copyright notice in the Description page of Project Settings.


#include "ZWConnectPlayerState.h"

#include "Cpp_CustomizationWidget.h"
#include "MMButton.h"
#include "TCPClient.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/ScrollBox.h"
#include "Components/TextBlock.h"
#include "Components/VerticalBox.h"
#include "Components/VerticalBoxSlot.h"



void AZWConnectPlayerState::BeginPlay()
{
	
	FString levelName = GetWorld()->GetMapName();
	levelName.RemoveFromStart(GetWorld()->StreamingLevelsPrefix);
	HasConfig =false;
	
	if (levelName == "LoginMenu") // change to == for working again on server
	{
		LoginWidget = CreateWidget<UUserWidget>(GetWorld(),LoginWidgetClass);
		LoginWidget->AddToViewport();
		loginButton = Cast<UButton>(  LoginWidget->GetWidgetFromName(TEXT("LoginButton")));
		if (loginButton)
		{
			UE_LOG(LogTemp, Log, TEXT("button set!"));
			loginButton->SetIsEnabled(true);
			loginButton->OnClicked.AddDynamic(this,  &AZWConnectPlayerState::OnLoginClick);
				
		}

		WarningBlock = Cast<UTextBlock>(LoginWidget->GetWidgetFromName(TEXT("WarningMessage")));
	
		canConnectToGameServer = false;
	}
	/*
	if (levelName == "MatchMakingMenu"){
		tcpClient = new TCPClient(this);
		canConnectToGameServer = false;
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow,FString::Printf(TEXT("s")));
	
		if ((MatchmakingWidgetClass) && (tcpClient->IsConnected()))
		{
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green,FString::Printf(TEXT("matchmaking Server Online")));
	
			ServersList = new TArray<FSessionInfo*>();
			GetWorld()->GetTimerManager().SetTimer(serverListTimerHandle,  this,
						&AZWConnectPlayerState::OnUpdateServerList, 2, true);
			
			MatchmakingWidget = CreateWidget<UUserWidget>(GetWorld(),MatchmakingWidgetClass);
			MatchmakingWidget->AddToViewport();

			NameInput = Cast<UEditableText>( MatchmakingWidget->GetWidgetFromName(TEXT("NameInput")));
			serverListScrollBoxWidget = Cast<UScrollBox>( MatchmakingWidget->GetWidgetFromName(TEXT("SessionScrollBox")));
			//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow,FString::Printf(TEXT("%s"),*serverListScrollBoxWidget->GetName()));
				/*
			UButton* newSessionButton = Cast<UButton>(  MatchmakingWidget->GetWidgetFromName(TEXT("NewSessionButton")));
			if (newSessionButton)
			{
				newSessionButton->SetIsEnabled(true);
				newSessionButton->OnClicked.AddDynamic(this,  &AZWConnectPlayerState::OnSendNameButtonClicked);
				
			}

			UButton* sendNameButton = Cast<UButton>(  MatchmakingWidget->GetWidgetFromName(TEXT("SendNameButton")));
			if (sendNameButton)
			{
				sendNameButton->SetIsEnabled(true);
				sendNameButton->OnClicked.AddDynamic(this,  &AZWConnectPlayerState::OnSendNameButtonClicked);
				
			}
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red,FString::Printf(TEXT("matchmaking Server Offline")));
	
		}
	}*/
}

void AZWConnectPlayerState::OnLoginClick()
{
	UE_LOG(LogTemp, Log, TEXT("button click!"));
	FIPv4Address tosend;
	UEditableText* IPInput = Cast<UEditableText>(LoginWidget->GetWidgetFromName(TEXT("MatchMackingIp")));
	UE_LOG(LogTemp, Log, TEXT("ipinput: '%s'"), *IPInput->GetText().ToString());

	if(	FIPv4Address::Parse(IPInput->GetText().ToString(),tosend))
	{
		UE_LOG(LogTemp, Log, TEXT("Parse OK"));
		FString f = tosend.ToString();
		UE_LOG(LogTemp, Log, TEXT("ip to copy: '%s'"),*f);
		MatchmakingIP = tosend;

	
		//UE_LOG(LogTemp, Log, TEXT("ipinput: '%s'"),tosend);
		tcpClient = new TCPClient(this);
		
		if ((LoginWidget )&&(tcpClient->IsConnected()))
		{
			UE_LOG(LogTemp, Log, TEXT("connected ! OK"));
			UEditableText* NameIN = Cast<UEditableText>(LoginWidget->GetWidgetFromName(TEXT("UsernameInput")));
			ClientName = NameIN->GetText().ToString();
			UEditableText* PassIN = Cast<UEditableText>(LoginWidget->GetWidgetFromName(TEXT("PasswordInput")));
			CLientPass = PassIN->GetText().ToString();
			tcpClient->SendPlayerLogin(ClientName,CLientPass);
		}
		
	}else
	{
		UE_LOG(LogTemp, Log, TEXT("errorOnclickParse"));
		FString error = "IP Adress input incorrect";
		WaringMessage(error,LoginWidget);
	}

}


void AZWConnectPlayerState::ShowCustomizationMenu()
{

	LoginWidget->RemoveFromViewport();
	CustomizationWidget = CreateWidget<UUserWidget>(GetWorld(),CustomizationWidgetClass);
	
	if(Cast<UCpp_CustomizationWidget>(CustomizationWidget))
	{
		
		
		CustomizationWidget->AddToViewport();
		UE_LOG(LogTemp, Log, TEXT("Customization Showing !"));
		ConnectToGameButton = Cast<UButton>(CustomizationWidget->GetWidgetFromName(TEXT("ConnectToGameButton")));
		
		if (ConnectToGameButton)
		{
			UE_LOG(LogTemp, Log, TEXT("Connect button set!"));
			ConnectToGameButton->SetIsEnabled(true);
			
			ConnectToGameButton->OnClicked.AddDynamic(this,  &AZWConnectPlayerState::OnConnectGameClick);
		}

		
	}

	
}



void AZWConnectPlayerState::OnConnectGameClick() 
{
	UE_LOG(LogTemp, Log, TEXT("Connect button Click!"));
	if(CustomizationWidget){
		UE_LOG(LogTemp, Log, TEXT("Send my config to server!"));
		FString CustomizationMessage = Cast<UCpp_CustomizationWidget>(CustomizationWidget)->GetConfigInString();
		UE_LOG(LogTemp, Log, TEXT("Cutomization To send: '%s'"), *CustomizationMessage);

		tcpClient->ConnectPlayerToGame(CustomizationMessage);
	}
	else
	{
		
		
	}
}

void AZWConnectPlayerState::WaitingForGame(bool waiting)
{
	ClientWaitingforGame = waiting;

	if(ClientWaitingforGame)
	{
		ConnectToGameButton = Cast<UButton>(CustomizationWidget->GetWidgetFromName(TEXT("ConnectToGameButton")));
		
		if (ConnectToGameButton)
		{
			UTextBlock* BTNText = Cast<UTextBlock>(CustomizationWidget->GetWidgetFromName("ConnectButtonText"));
			FString btnTextSet ="Cancel MatchMaking";
			BTNText->SetText(FText::FromString(btnTextSet));
			
		}
	}
	else
	{
		UTextBlock* BTNText = Cast<UTextBlock>(CustomizationWidget->GetWidgetFromName("ConnectButtonText"));
		FString f= "Connect to Game";
		BTNText->SetText(FText::FromString(f));
	}	
	
}


void AZWConnectPlayerState::ReceiveWarriorConfigUI(int w,int a1,int a2, int a3)
{
	Config.WarriorID=w;
	Config.Ability1=a1;
	Config.Ability2=a2;
	Config.Ability3=a3;
	HasConfig = true;
}

void AZWConnectPlayerState::WaringMessage(FString msg,UUserWidget* WidgetOfWarning)
{
	WarningBlock->Text = FText::FromString("Warning:"+'\n'+msg);
}




void AZWConnectPlayerState::SendNameFromInput()
{
	if(NameInput)
	{
		FString name =  NameInput->GetText().ToString();
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow,name);
			
		tcpClient->SendMessageToServer(name);
	}
	
	
}









void AZWConnectPlayerState::UpdateCanvas()
{
	
}

void AZWConnectPlayerState::GotoGameLevel()
{
	if(tcpClient)
	{
		if (tcpClient->IsConnected() && CustomizationWidget){
			UE_LOG(LogTemp, Log, TEXT("Send my config to server!"));
			FString CustomizationMessage = Cast<UCpp_CustomizationWidget>(CustomizationWidget)->GetConfigInString();
			UE_LOG(LogTemp, Log, TEXT("Cutomization To send: '%s'"), *CustomizationMessage);
			
			APlayerController* pController = GetWorld()->  GetFirstPlayerController();
			
			if (pController)
			{
				FString cmd = "open " + tcpClient->getGameIP() + " " +CustomizationMessage;
				tcpClient->Stop();
				canConnectToGameServer = false;
				CustomizationWidget->RemoveFromViewport();
				pController->ConsoleCommand(cmd);
			}
			
		}
		
	}
	
}


/*

void AZWConnectPlayerState::OnUpdateServerList()
{
	if (tcpClient)
	{
		if (tcpClient->IsConnected())
		{
			if (ServersList->Num() > 0)
			{
				if ((MatchmakingWidget) && (serverListScrollBoxWidget)) {
					TArray<UWidget*> allChildren = serverListScrollBoxWidget->  GetAllChildren();
					for (int i = 0; i < allChildren.Num(); i++)
					{
						allChildren[i]->RemoveFromParent();	
					}
					
					for (int i = 0; i < ServersList->Num(); i++) {
						UVerticalBox* ItemWidgetsBox = NewObject<UVerticalBox>();
						serverListScrollBoxWidget->AddChild(ItemWidgetsBox);
						UMMButton* ItemWidget = NewObject<UMMButton>(this);
						ItemWidget->SetSessionInfo((*ServersList)[i]->id,  tcpClient);
						UTextBlock* ItemWidgetText = NewObject<UTextBlock>();
						ItemWidgetText->SetText(FText::FromString(  (*ServersList)[i]->name));
						ItemWidget->AddChild(ItemWidgetText);

						UVerticalBoxSlot* Slot = ItemWidgetsBox->AddChildToVerticalBox(ItemWidget);
						static FMargin Padding(5);
						Slot->SetPadding(Padding);
					}
					
				}
			}

			if (canConnectToGameServer)
			{
				APlayerController* pController = GetWorld()->  GetFirstPlayerController();
				
				
				if (pController)
				{
					FString cmd = "open " + connectToGameServerSession.serverip+":" + FString::FromInt(connectToGameServerSession.serverport);
					tcpClient->Stop();
					canConnectToGameServer = false;
					MatchmakingWidget->RemoveFromViewport();
					pController->ConsoleCommand(cmd);
				}
			}
		}
	}
}


void AZWConnectPlayerState::UpdateSessionsList(FString Serverinfo)
{
	TArray<FString> Out;
	Serverinfo.ParseIntoArray(Out, TEXT("|"), true);
	for (int i = 1; i < Out.Num() - 1; i += 2)
	{
		FSessionInfo *tempInfo = new FSessionInfo();
		tempInfo->id = FCString::Atoi(*Out[i]);
		tempInfo->name = Out[i + 1];
		tempInfo->serverip = "";
		tempInfo->serverport = -1;
		ServersList->Add(tempInfo);
	}
}

void AZWConnectPlayerState::ConnectToGameServer(FSessionInfo session)
{
	canConnectToGameServer = true;
	connectToGameServerSession = session;  
}

*/


