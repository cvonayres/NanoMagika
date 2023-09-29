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

	// Server / Client Ready
	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;

	/** Combat Interface */
	virtual int32 GetPlayerLevel() override;
	/** end Combat Interface */
	
protected:
	virtual void BeginPlay() override;

	// Init Ability System
	virtual void InitAbilityActorInfo() override;

private:
	UPROPERTY()
	class AECMPlayerController* ControllerRef;
	UPROPERTY()
	class AECMPlayerState* PlayerStateRef;
	
	// Called from Player Controller
	void UpdatedViewMode();

};
