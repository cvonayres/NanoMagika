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
class USplineComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnActionBindingRequested, UECMInputComponent*, InputComponent);

UCLASS()
class NANOMAGIKA_API AECMPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AECMPlayerController();

	virtual void PreInitializeComponents() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	// Delegate to request binding an action
	UPROPERTY(BlueprintAssignable, Category = "Input")
	FOnActionBindingRequested OnActionBindingRequested;

	
	// Helper functions
	UECMInputComponent* GetInputComponent() const { return ECMInputComponent;}
	TObjectPtr<APlayerCameraManager> GetPCM() const { return PlayerCameraManager;}

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

	// Input Component, Context & Config
	UPROPERTY()
	UECMInputComponent* ECMInputComponent = nullptr;
	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputMappingContext> InputContext = nullptr;
	UPROPERTY(EditDefaultsOnly, Category="Input")
	TObjectPtr<UECMInputConfig> InputConfig;

	UECMAbilitySystemComponent* GetASC();
	UPROPERTY()
	TObjectPtr<	UECMAbilitySystemComponent> ECMAbilitySystemComponent;

	void InitActionBindings();
	UPROPERTY()
	FTimerHandle InitActionBindingsTimerHandle = FTimerHandle();
	
	virtual void AbilityInputTagPressed(FGameplayTag InputTag);
	virtual void AbilityInputTagReleased(FGameplayTag InputTag);
	virtual void AbilityInputTagHeld(FGameplayTag InputTag);

};
