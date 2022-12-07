// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePlayerController.h"

#include "PlayableCharacter.h"
#include "GameFramework/Character.h"

ABasePlayerController::ABasePlayerController()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Crosshairs;
}


void ABasePlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	if(!CachedMoveableInterface || !CachedCharacterInterface)
	{
		CachedCharacterInterface = Cast<IUsableCharacterSkillSlot>(GetCharacter());
		CachedMoveableInterface = Cast<IMoveableCharacter>(GetCharacter());
	}
	
	CalculateMousePosition();
}

void ABasePlayerController::BeginPlay()
{
	Super::BeginPlay();

	ACharacter* InCharacter = GetCharacter();

	CachedCharacterInterface = Cast<IUsableCharacterSkillSlot>(InCharacter);
	CachedMoveableInterface = Cast<IMoveableCharacter>(InCharacter);

	PlayableCharacter = Cast<APlayableCharacter>(InCharacter);
}

void ABasePlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAction("BasicAbility", IE_Pressed, this, &ABasePlayerController::BasicAttackPressed);
	InputComponent->BindAction("SpecialAbility1", IE_Pressed, this, &ABasePlayerController::FirstAbilityPressed);
	InputComponent->BindAction("SpecialAbility2", IE_Pressed, this, &ABasePlayerController::SecondAbilityPressed);
	InputComponent->BindAction("SpecialAbility3", IE_Pressed, this, &ABasePlayerController::ThirdAbilityPressed);
	InputComponent->BindAxis("MoveVertical", this, &ABasePlayerController::MoveVerticalInput);
	InputComponent->BindAxis("MoveHorizontal", this, &ABasePlayerController::MoveHorizontalInput);
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

void ABasePlayerController::MoveVerticalInput(float Value)
{
	if (CachedMoveableInterface && Value != 0)
	{
		// TODO WORKS
		// PlayableCharacter->MoveVertical_Implementation(Value);
		// TODO DOESNT WORK
		// PlayableCharacter->MoveVertical(Value);
		// TODO DOESNT WORK
		CachedMoveableInterface->MoveVertical(Value);
	}
}

void ABasePlayerController::MoveHorizontalInput(float Value)
{
	if (CachedMoveableInterface && Value != 0)
	{
		// TODO WORKS
		// PlayableCharacter->MoveHorizontal_Implementation(Value);
		// TODO DOESNT WORK
		// PlayableCharacter->MoveHorizontal(Value);
		// TODO DOESNT WORK
		CachedMoveableInterface->MoveHorizontal(Value);
	}
}

void ABasePlayerController::MouseChanged(FVector Value)
{
	if (CachedMoveableInterface)
	{
		CachedMoveableInterface->MoveMouse(Value);
	}
}

void ABasePlayerController::CalculateMousePosition()
{
	FHitResult TraceHitResult;
	this->GetHitResultUnderCursor(ECC_Visibility, true, TraceHitResult);
	const FVector CursorFv = TraceHitResult.ImpactNormal;
	const FRotator CursorR = CursorFv.Rotation();
	MouseChanged(TraceHitResult.Location);
}
