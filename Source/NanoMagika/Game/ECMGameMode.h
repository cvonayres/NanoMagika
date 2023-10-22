// Copyright Electronic CAD Monkey [ECM]

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ECMGameMode.generated.h"

class UECMCharacterClassInfo;

UCLASS

()
class NANOMAGIKA_API AECMGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	
	UPROPERTY(EditDefaultsOnly, Category="CharacterClassDefaults")
	TObjectPtr<UECMCharacterClassInfo> CharacterClassInfo;

	
};
