// Fill out your copyright notice in the Description page of Project Settings.


#include "GameState2v2.h"

void AGameState2v2::BeginPlay()
{
	Super::BeginPlay();
	GameMode = Cast<AGameMode2v2>(GetWorld()->GetAuthGameMode());
}
