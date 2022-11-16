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

void ABasePlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	CachedCharacterInterface = Cast<IUsableCharacterSkillSlot>(InPawn);
	CachedMoveableInterface = Cast<IMoveableCharacter>(InPawn);
}

void ABasePlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAction("BasicAbility", IE_Pressed, this, &ABasePlayerController::BasicAttackPressed);
	InputComponent->BindAction("SpecialAbility1", IE_Pressed, this, &ABasePlayerController::FirstAbilityPressed);
	InputComponent->BindAction("SpecialAbility2", IE_Pressed, this, &ABasePlayerController::SecondAbilityPressed);
	InputComponent->BindAction("SpecialAbility3", IE_Pressed, this, &ABasePlayerController::ThirdAbilityPressed);
	InputComponent->BindAxis("MoveVertical",this,&ABasePlayerController::MoveVertical);
	InputComponent->BindAxis("MoveHorizontal",this,&ABasePlayerController::MoveHorizontal);
	
}

void ABasePlayerController::BasicAttackPressed()
{
	if (CachedCharacterInterface && !CachedCharacterInterface->GetIsCasting())
	{
		CachedCharacterInterface->UseBasicAttack();
	}
}

void ABasePlayerController::FirstAbilityPressed()
{
	if (CachedCharacterInterface && !CachedCharacterInterface->GetIsCasting())
	{
		CachedCharacterInterface->UseFirstAbility();
	}
}

void ABasePlayerController::SecondAbilityPressed()
{
	if (CachedCharacterInterface && !CachedCharacterInterface->GetIsCasting())
	{
		CachedCharacterInterface->UseSecondAbility();
	}
}

void ABasePlayerController::ThirdAbilityPressed()
{
	if (CachedCharacterInterface && !CachedCharacterInterface->GetIsCasting())
	{
		CachedCharacterInterface->UseThirdAbility();
	}
}

void ABasePlayerController::MoveVertical(float Value)
{
	CachedMoveableInterface->MoveVertical(Value);
}

void ABasePlayerController::MoveHorizontal(float Value)
{
	CachedMoveableInterface->MoveHorizontal(Value);
}
