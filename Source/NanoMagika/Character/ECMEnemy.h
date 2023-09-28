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

protected:
	virtual void BeginPlay() override;
	virtual void InitAbilityActorInfo() override;
	
};
