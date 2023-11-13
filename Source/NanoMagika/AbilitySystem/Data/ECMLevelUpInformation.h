// Copyright Electronic CAD Monkey [ECM]

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "ECMLevelUpInformation.generated.h"

USTRUCT(BlueprintType)
struct FECMLevelUpInfo
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int32  LevelUpThreshold;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int32  AttributePointAwarded;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int32  AbilityPointAwarded;

	FECMLevelUpInfo()
	{
		LevelUpThreshold = 0;
		AttributePointAwarded = 1;
		AbilityPointAwarded = 1;
	}
};

UCLASS()
class NANOMAGIKA_API UECMLevelUpInformation : public UDataAsset
{
	GENERATED_BODY()
	
public:
	int32 FindLevelForXP(int32 XP) const;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Level Up Info")
	TArray<FECMLevelUpInfo> LevelUpInformation;
};


