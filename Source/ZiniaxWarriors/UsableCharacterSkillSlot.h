// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "UsableCharacterSkillSlot.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UUsableCharacterSkillSlot : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class ZINIAXWARRIORS_API IUsableCharacterSkillSlot
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void UseBasicAttack() = 0;
	virtual void UseFirstAbility() = 0;
	virtual void UseSecondAbility() = 0;
	virtual void UseThirdAbility() = 0;

	bool GetIsCasting() const { return bIsCasting; }
	void SetIsCasting(bool Setter) { bIsCasting = Setter; }

protected:
	bool bIsCasting = false;
};
