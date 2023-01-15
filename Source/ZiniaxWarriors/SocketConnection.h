// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SocketConnection.generated.h"

UCLASS()
class ZINIAXWARRIORS_API ASocketConnection : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASocketConnection();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UFUNCTION(BlueprintCallable)
		void SendConnectInfo();
	UFUNCTION(BlueprintCallable)
	void StopMatchmaking();
	UFUNCTION(BlueprintCallable)
		void EndGame();
	FSocket* Socket;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FString PlayerName;
	// For Server just send " |";
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FString PlayerPass;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FString IpString;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FString OptionsString;
	int ID = 0;
};
