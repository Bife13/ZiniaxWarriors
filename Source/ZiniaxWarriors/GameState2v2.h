// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/GameState.h"
#include "GameState2v2.generated.h"


DECLARE_EVENT(AGameState2v2,ResetRound)
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FScoreUpdate,int, Rounds,int,Team1, int, Team2);
/**
 * 
 */
UCLASS()
class ZINIAXWARRIORS_API AGameState2v2 : public AGameState
{
	GENERATED_BODY()
	
public:




	UPROPERTY(BlueprintAssignable)
	FScoreUpdate ScoreUpdate;


	ResetRound ResetEvent;
	UPROPERTY()
	int Team1Rounds =0;

	UPROPERTY()
	int Team2Rounds =0;
	
	UPROPERTY()
	int Rounds =1;
	
	UPROPERTY()
	int Minutes;
	
	UPROPERTY()
	int Seconds;

	UFUNCTION(BlueprintCallable)
	int GetTeam1Rounds();
	UFUNCTION()
	void SetTeam1Rounds(int T1Rounds);
	UFUNCTION(BlueprintCallable)
	int GetTeam2Rounds();
	UFUNCTION()
	void SetTeam2Rounds(int T2Rounds);
	UFUNCTION(BlueprintCallable)
	int GetRoundNumber();
	UFUNCTION(NetMulticast, Reliable)
	void SetRounds(int RoundsToSet);
	UFUNCTION(BlueprintCallable)
	int GetMinutes();
	UFUNCTION()
	void SetMinutes(int MinutesToSet);
	UFUNCTION(BlueprintCallable)
	int GetSeconds();
	UFUNCTION()
	void SetSeconds(int Secondstoset);

	UFUNCTION(NetMulticast, Reliable)
	void SetAllRounds(int round, int t1, int t2);
	
	UFUNCTION(NetMulticast, Reliable)
	void OnScoreChanged();


	//UFUNCTION(NetMulticast,BlueprintImplementableEvent)
	//	void InformClients();


};
