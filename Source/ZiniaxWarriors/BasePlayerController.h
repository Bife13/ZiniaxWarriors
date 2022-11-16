// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
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

protected:
	// Begin PlayerController interface
	virtual void PlayerTick(float DeltaTime) override;
	virtual void SetupInputComponent() override;
	virtual void OnPossess(APawn* InPawn) override;


	void BasicAttackPressed();
	void FirstAbilityPressed();
	void SecondAbilityPressed();
	void ThirdAbilityPressed();

	void MoveVertical(float Value);
	void MoveHorizontal(float Value);

	IUsableCharacterSkillSlot* CachedCharacterInterface;
	APlayableCharacter* Char;
};
