// Copyright Electronic CAD Monkey [ECM]

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "ECMCharacterClassInfo.generated.h"

class UGameplayEffect;

UENUM(BlueprintType)
enum class  ECharacterClass : uint8
{
	Melee,
	Ranged,
	Tech,
	Mage
};

USTRUCT(BlueprintType)
struct FCharacterClassDefaultInfo
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, Category="ClassDefaults")
	TSubclassOf<UGameplayEffect> PrimaryAttribute;

};

UCLASS()
class NANOMAGIKA_API UECMCharacterClassInfo : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, Category="CharacterClassDefaults")
	TMap<ECharacterClass, FCharacterClassDefaultInfo> CharacterClassInformation;

	UPROPERTY(EditDefaultsOnly, Category="CommonClassDefaults")
	TSubclassOf<UGameplayEffect> VitalAttribute;
	
	UPROPERTY(EditDefaultsOnly, Category="CommonClassDefaults")
	TSubclassOf<UGameplayEffect> SecondaryAttribute;

	FCharacterClassDefaultInfo GetClassDefaultInfo(ECharacterClass CharacterClass);
	
};
