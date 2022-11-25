#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"

#include "DTR_CharacterStats.generated.h"


USTRUCT(Blueprintable)
struct FCharacterStats : public FTableRowBase
{
	GENERATED_BODY()
	
<<<<<<< HEAD
	UPROPERTY(BlueprintReadWrite)
	float Power;

	UPROPERTY(BlueprintReadWrite)
	float Speed;
	
	UPROPERTY(BlueprintReadWrite)
	float MaximumHealth;
	
	UPROPERTY(BlueprintReadWrite)
	float Resistance;
	
	UPROPERTY(BlueprintReadWrite)
=======
	UPROPERTY(EditInstanceOnly,BlueprintReadWrite)
	float Power;
	UPROPERTY(EditInstanceOnly,BlueprintReadWrite)
	float Speed;
	UPROPERTY(EditInstanceOnly,BlueprintReadWrite)
	float MaximumHealth;
	UPROPERTY(EditInstanceOnly,BlueprintReadWrite)
	float Resistance;
	UPROPERTY(EditInstanceOnly,BlueprintReadWrite)
>>>>>>> master-bife
	float ViewRange;
	
};
