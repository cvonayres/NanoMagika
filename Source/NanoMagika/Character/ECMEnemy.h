// Copyright Electronic CAD Monkey [ECM]

#pragma once

#include "CoreMinimal.h"
#include "ECMCharacterBase.h"
#include "ECMEnemy.generated.h"

UCLASS()
class NANOMAGIKA_API AECMEnemy : public AECMCharacterBase
{
	GENERATED_BODY()

public:
	AECMEnemy();

	/** Combat Interface */
	FORCEINLINE virtual int32 GetPlayerLevel() override { return Level; }
	/** end Combat Interface */

protected:
	virtual void BeginPlay() override;
	
	virtual void InitializeCharacter() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Character Class Defaults")
	int32 Level = 1;
	
};
