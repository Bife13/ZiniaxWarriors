// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MoveableCharacter.h"
#include "PlayableCharacter.h"
#include "UsableCharacterSkillSlot.h"
#include "GameFramework/PlayerController.h"
#include "BasePlayerController.generated.h"

/**
 * 
 */
UCLASS()
class ZINIAXWARRIORS_API ABasePlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ABasePlayerController();
	// void OnCharacterPossess(ACharacter* InCharacter) ;
	UFUNCTION()
	void CharacterActivate();

	UFUNCTION()
	void CharacterDeactivate();

protected:
	// Begin PlayerController interface
	virtual void PlayerTick(float DeltaTime) override;
	virtual void SetupInputComponent() override;
	virtual void BeginPlay() override;

	UPROPERTY()
	APlayableCharacter* PlayableCharacter;


	void BasicAttackPressed();
	void FirstAbilityPressed();
	void SecondAbilityPressed();
	void ThirdAbilityPressed();
	void MoveVerticalInput(float Value);
	void MoveHorizontalInput(float Value);
	void MouseChanged(FVector Value);
	void CalculateMousePosition();

	IUsableCharacterSkillSlot* CachedCharacterInterface;
	IMoveableCharacter* CachedMoveableInterface;

	UPROPERTY(Replicated)
	bool bIsCharacterActivated = false;
};
