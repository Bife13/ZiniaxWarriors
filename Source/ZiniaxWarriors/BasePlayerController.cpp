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

	InputComponent->BindAction("BasicAbility", IE_Pressed, this, &ABasePlayerController::BasicAttackPressed);
	InputComponent->BindAction("SpecialAbility1", IE_Pressed, this, &ABasePlayerController::FirstAbilityPressed);
	InputComponent->BindAction("SpecialAbility2", IE_Pressed, this, &ABasePlayerController::SecondAbilityPressed);
	InputComponent->BindAction("SpecialAbility3", IE_Pressed, this, &ABasePlayerController::ThirdAbilityPressed);
}

void ABasePlayerController::BasicAttackPressed()
{
	if (CachedPawnInterface)
	{
		CachedPawnInterface->UseBasicAttack();
	}
}

void ABasePlayerController::FirstAbilityPressed()
{
	if (CachedPawnInterface)
	{
		CachedPawnInterface->UseFirstAbility();
	}
}

void ABasePlayerController::SecondAbilityPressed()
{
	if (CachedPawnInterface)
	{
		CachedPawnInterface->UseSecondAbility();
	}
}

void ABasePlayerController::ThirdAbilityPressed()
{
	if (CachedPawnInterface)
	{
		CachedPawnInterface->UseThirdAbility();
	}
}
