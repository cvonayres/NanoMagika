// Copyright Electronic CAD Monkey [ECM]

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GameplayTagContainer.h"
#include "ECMPlayerController.generated.h"

class UECMDamageTextComponent;
class AECMPlayerCameraManager;
class UECMInputComponent;
class UECMInputConfig;
class UInputMappingContext;
class UInputAction;
class UECMAbilitySystemComponent;
struct FInputActionValue;
class USplineComponent;

UCLASS()
class NANOMAGIKA_API AECMPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AECMPlayerController();

	// Includes for participation in modular gameplay plugin
	virtual void PreInitializeComponents() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	
	// Helper functions
	UECMInputComponent* GetInputComponent() const { return ECMInputComponent;}
	TObjectPtr<UECMInputConfig> GetInputConfig() const { return InputConfig;}

	TObjectPtr<APlayerCameraManager> GetPCM() const { return PlayerCameraManager;}

	UFUNCTION(Client,Reliable)
	void ShowDamageNumber(float Damage, ACharacter* TargetCharacter, bool bBlockHit, bool bCriticalHit);

	
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

	// Functions tied to Input Tag pressed, released and help, overridden in child classes
	virtual void AbilityInputTagPressed(FGameplayTag InputTag);
	virtual void AbilityInputTagReleased(FGameplayTag InputTag);
	virtual void AbilityInputTagHeld(FGameplayTag InputTag);

	// Useful pointers
	UPROPERTY()
	UECMAbilitySystemComponent* ECMCharacterASC = nullptr;

	// Helper functions
	bool GetECMCharacterASC();
	bool CheckCameraMode(FName TagName);

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UECMDamageTextComponent> DamageTextComponentClass;
};
