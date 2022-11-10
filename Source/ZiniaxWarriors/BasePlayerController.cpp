// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePlayerController.h"

ABasePlayerController::ABasePlayerController()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Crosshairs;
}


void ABasePlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);
}

void ABasePlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
}
