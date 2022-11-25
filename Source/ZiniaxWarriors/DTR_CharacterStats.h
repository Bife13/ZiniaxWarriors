#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"

#include "DTR_CharacterStats.generated.h"


USTRUCT(Blueprintable)
struct FCharacterStats : public FTableRowBase
{
	GENERATED_BODY()
	
	UPROPERTY(EditInstanceOnly,BlueprintReadWrite)
	float Power;
	UPROPERTY(EditInstanceOnly,BlueprintReadWrite)
	float Speed;
	UPROPERTY(EditInstanceOnly,BlueprintReadWrite)
	float MaximumHealth;
	UPROPERTY(EditInstanceOnly,BlueprintReadWrite)
	float Resistance;
	UPROPERTY(EditInstanceOnly,BlueprintReadWrite)
	float ViewRange;
	
};
