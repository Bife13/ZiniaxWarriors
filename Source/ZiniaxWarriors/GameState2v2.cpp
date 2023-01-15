// Fill out your copyright notice in the Description page of Project Settings.


#include "GameState2v2.h"





int AGameState2v2::GetTeam1Rounds()
{
	return Team1Rounds;
}

void AGameState2v2::SetTeam1Rounds(int T1Rounds)
{
	Team1Rounds = T1Rounds;
}

int AGameState2v2::GetTeam2Rounds()
{
	return Team2Rounds;
}

void AGameState2v2::SetTeam2Rounds(int T2Rounds)
{
	Team2Rounds=T2Rounds;
}

int AGameState2v2::GetRoundNumber()
{
	return Rounds;
}

void AGameState2v2::SetRounds(int roundstoset)
{
	Rounds =roundstoset;
	OnScoreChanged();
	
}

int AGameState2v2::GetMinutes()
{
	return Minutes;
}

void AGameState2v2::SetMinutes(int Minutestoset)
{
	Minutes = Minutestoset;
}

int AGameState2v2::GetSeconds()
{
	return Seconds;
}

void AGameState2v2::SetSeconds(int Secondstoset)
{
	Seconds=Secondstoset;
}

void AGameState2v2::SetAllRounds(int round,int t1,int t2)
{
	Team1Rounds = t1;
	Team2Rounds = t2;
	Rounds=round;
	OnScoreChanged();
}

void AGameState2v2::OnScoreChanged_Implementation()
{

	UE_LOG(LogTemp, Warning, TEXT("Round: %d , TEAM1: %d, TEAM2: %d"), Rounds,Team1Rounds,Team2Rounds);
	ScoreUpdate.Broadcast(Rounds,Team1Rounds,Team2Rounds);
}
