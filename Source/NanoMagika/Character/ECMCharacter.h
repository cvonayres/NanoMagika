// Copyright Electronic CAD Monkey [ECM]

#pragma once

#include "CoreMinimal.h"
#include "ECMCharacterBase.h"
#include "ECMCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;

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
	// Init Ability System
	virtual void InitializeCharacter() override;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USpringArmComponent> SpringArmComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCameraComponent> CameraComponent;
	
	// Controller and Player State Ref
	UPROPERTY()
	class AECMPlayerController* ControllerRef;
	UPROPERTY()
	class AECMPlayerState* PlayerStateRef;
	
	// Called when we have a valid player controller
	void InitHUD() const;
};
