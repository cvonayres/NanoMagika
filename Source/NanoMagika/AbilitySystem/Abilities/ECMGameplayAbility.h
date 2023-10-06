// Copyright Electronic CAD Monkey [ECM]

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "ECMGameplayAbility.generated.h"

UCLASS()
class NANOMAGIKA_API UECMGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()

public:

	UPROPERTY(EditDefaultsOnly, Category="Input")
	FGameplayTag StartupInputTag;
	
};
