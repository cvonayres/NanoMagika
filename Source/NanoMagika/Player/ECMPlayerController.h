// Copyright Electronic CAD Monkey [ECM]

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GameplayTagContainer.h"
#include "ECMPlayerController.generated.h"

class AECMPlayerCameraManager;
class UECMInputComponent;
class UECMInputConfig;
class UInputMappingContext;
class UInputAction;
class UECMAbilitySystemComponent;
struct FInputActionValue;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FTickSigniture, const FHitResult&, CursorHit);
UCLASS()
class NANOMAGIKA_API AECMPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AECMPlayerController();

	virtual void PreInitializeComponents() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	
	// Delegate for CursorHit calls
	FTickSigniture CursorHitEvent;

	// Helper fucntions
	UECMInputComponent* GetInputComponent() const { return ECMInputComponent;}
	TObjectPtr<APlayerCameraManager> GetPCM() const { return PlayerCameraManager;}
	
protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

private:
	// Input Component, Context & Config
	UPROPERTY()
	UECMInputComponent* ECMInputComponent = nullptr;
	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputMappingContext> InputContext = nullptr;
	UPROPERTY(EditDefaultsOnly, Category="Input")
	TObjectPtr<UECMInputConfig> InputConfig;

	// Input Actions
	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputAction> MoveAction = nullptr;

	UPROPERTY()
	TObjectPtr<	UECMAbilitySystemComponent> ECMAbilitySystemComponent;

	void Move(const FInputActionValue& InputActionValve);

	void InitMouse();
	void CursorTrace() const;

	void AbilityInputTagPressed(FGameplayTag InputTag);
	void AbilityInputTagReleased(FGameplayTag InputTag);
	void AbilityInputTagHeld(FGameplayTag InputTag);

	UECMAbilitySystemComponent* GetASC();
};
