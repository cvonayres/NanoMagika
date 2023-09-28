// Copyright Electronic CAD Monkey [ECM]

#pragma once

#include "CoreMinimal.h"
#include "ECMCharacterBase.h"
#include "ECMCharacter.generated.h"


UCLASS()
class NANOMAGIKA_API AECMCharacter : public AECMCharacterBase
{
	GENERATED_BODY()

public:
	AECMCharacter();

	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;
	
protected:
	virtual void BeginPlay() override;

	virtual void InitAbilityActorInfo() override;

private:
	UPROPERTY()
	class AECMPlayerController* ControllerRef;

	// Called from Player Controller
	void UpdatedViewMode();

};
