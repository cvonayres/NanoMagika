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
	UECMGameplayAbility();
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Default")
	int32 AbilityLevel = 1;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Default")
	bool BindToInputTag = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Default", meta = (EditCondition = BindToInputTag))
	FGameplayTag InputTag = FGameplayTag();

};
