#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"

#include "DTR_CharacterStats.generated.h"


USTRUCT(Blueprintable)
struct FCharacterStats : public FTableRowBase
{
	GENERATED_BODY()
	
	UPROPERTY(BlueprintReadWrite)
	float Power;

	UPROPERTY(BlueprintReadWrite)
	float Speed;
	
	UPROPERTY(BlueprintReadWrite)
	float MaximumHealth;
	
	UPROPERTY(BlueprintReadWrite)
	float Resistance;
	
	UPROPERTY(BlueprintReadWrite)
	float ViewRange;
	
};
