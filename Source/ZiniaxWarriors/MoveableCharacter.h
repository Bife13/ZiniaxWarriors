// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "MoveableCharacter.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UMoveableCharacter : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class ZINIAXWARRIORS_API IMoveableCharacter
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void MoveVertical(float Value) = 0;
	virtual void MoveHorizontal(float Value) = 0;
	virtual void MoveMouse(FVector MousePosition) = 0;
};
