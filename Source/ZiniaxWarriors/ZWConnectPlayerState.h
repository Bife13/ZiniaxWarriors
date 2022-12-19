// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"


#include "Components/Button.h"
#include "Components/EditableText.h"
#include "Components/ScrollBox.h"
#include "Components/TextBlock.h"
#include "GameFramework/PlayerState.h"
#include "Interfaces/IPv4/IPv4Address.h"
#include "ZWConnectPlayerState.generated.h"

/**
 * 
 */
USTRUCT() 
struct FSessionInfo
{
	GENERATED_BODY()
	UPROPERTY()
	int id;
	UPROPERTY()
	FString name;
	UPROPERTY()
	FString serverip;
	UPROPERTY()
	int serverport;
};

USTRUCT() 
struct FWarriorConfig
{
	GENERATED_BODY()
	UPROPERTY()
	int WarriorID;
	
	UPROPERTY()
	int Ability1;
	
	UPROPERTY()
	int Ability2;
	
	UPROPERTY()
	int Ability3;
};



UCLASS()
class ZINIAXWARRIORS_API AZWConnectPlayerState : public APlayerState
{
	GENERATED_BODY()
	public:
	void UpdateSessionsList(FString Serverinfo);
	void ConnectToGameServer(FSessionInfo session);
	UFUNCTION()
	void GotoGameLevel();
	UFUNCTION()
	void SendNameFromInput();
	UPROPERTY()
	FString ClientName;
	UPROPERTY()
	FString CLientPass;
	UPROPERTY()
	int WarriorID;
	
	FIPv4Address MatchmakingIP;
	UFUNCTION()
	void ShowCustomizationMenu();

	UFUNCTION()
	void ReceiveWarriorConfigUI(int w, int a1, int a2, int a3);

	UFUNCTION()
	void OnConnectGameClick();

	UFUNCTION()
	void WaitingForGame(bool waiting);
	bool ClientWaitingforGame;

	UFUNCTION()
	void UpdateCanvas();
	bool HasConfig;
protected:
	virtual void BeginPlay() override;
	UFUNCTION()
	void OnLoginClick();
	
	UFUNCTION()
	void WaringMessage(FString msg, UUserWidget* WidgetOfWarning);
	//UPROPERTY(VisibleAnywhere)
	class TCPClient* tcpClient;
	
	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UUserWidget> MatchmakingWidgetClass;
	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UUserWidget> LoginWidgetClass;

	UPROPERTY(VisibleAnywhere, Category = "UI")
	TSubclassOf<UUserWidget> CustomizationWidgetClass;
	
	UPROPERTY(VisibleAnywhere,Category = "UI")
	UUserWidget* MatchmakingWidget;
	UPROPERTY(VisibleAnywhere,Category = "UI")
	UUserWidget* LoginWidget;
	UPROPERTY(VisibleAnywhere,Category = "UI")
	UUserWidget* CustomizationWidget;
	UPROPERTY(VisibleAnywhere,Category = "UI")
		UUserWidget* CustomizationManager;
	UPROPERTY(VisibleAnywhere,Category = "UI")
	UScrollBox* serverListScrollBoxWidget;

	UPROPERTY(VisibleAnywhere,Category = "UI")
	UButton* loginButton;

	UPROPERTY(VisibleAnywhere,Category = "UI")
	UButton* ConnectToGameButton;
	
	UPROPERTY(VisibleAnywhere,Category = "UI")
	UTextBlock* WarningBlock;
	
	TArray<FSessionInfo*> *ServersList;
	FTimerHandle serverListTimerHandle;

	bool canConnectToGameServer;

	FSessionInfo connectToGameServerSession;

	FWarriorConfig Config;
	UPROPERTY(VisibleAnywhere,Category = "UI")
	UEditableText* NameInput;

	UPROPERTY(VisibleAnywhere,Category = "UI")
	UEditableText* ClientNameInput;
	UPROPERTY(VisibleAnywhere,Category = "UI")
	UEditableText* ClientPassInput;
	
	UFUNCTION()
	void OnUpdateServerList(); 
};
