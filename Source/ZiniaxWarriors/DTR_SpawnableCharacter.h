#pragma once

#include "CoreMinimal.h"
#include "PlayableCharacter.h"
#include "Engine/DataTable.h"

#include "DTR_SpawnableCharacter.generated.h"


USTRUCT(Blueprintable)
struct FSpawnableCharacter : public FTableRowBase
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<APlayableCharacter> PlayableCharacter;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FString Description;
};
