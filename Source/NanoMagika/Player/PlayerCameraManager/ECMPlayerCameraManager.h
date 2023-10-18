// Copyright Electronic CAD Monkey [ECM]

#pragma once

#include "CoreMinimal.h"
#include "DA_CameraMode.h"
#include "Camera/PlayerCameraManager.h"
#include "ECMPlayerCameraManager.generated.h"

class AECMCharacter;
class UAbilitySystemComponent;
class UCharacterMovementComponent;
class UInputAction;
class UCameraComponent;
class USpringArmComponent;
struct FInputActionValue;

UENUM(BlueprintType)
enum class ECameraMode : uint8
{
	FirstPersonView UMETA(DisplayName = "First Person View"),
	ThirdPersonView UMETA(DisplayName = "Third Person View"),
	TopDownView     UMETA(DisplayName = "Top Down View")
};

UCLASS()
class NANOMAGIKA_API AECMPlayerCameraManager : public APlayerCameraManager
{
	GENERATED_BODY()

public:
	UFUNCTION(Category="Camera")
	void InitPCM(const ACharacter* Character);
	
	UFUNCTION(BlueprintCallable, Category="Camera")
	void UpdateCameraMode(UDA_CameraMode* CameraModeDA, const FGameplayTag AddTag, const FGameplayTag RemoveTag1, const FGameplayTag RemoveTag2);

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Camera")
	TObjectPtr<UDA_CameraMode> FPV_Settings;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Camera")
	TObjectPtr<UDA_CameraMode> TPV_Settings;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Camera")
	TObjectPtr<UDA_CameraMode> TDV_Settings;

private:
	FTimerHandle TimerHandle_GetPawnAndController;
	float TimeElapsedTrying = 0.0f;
	float TimeLimitForCheck = 10.0f;  // Time limit, in seconds.
	float CheckInterval = 0.5f;       // Interval to check, in seconds.

	// Bind Enhanced Inputs
	void BindInputs();
	virtual void AbilityInputTagPressed(FGameplayTag InputTag);

	// Zoom Controls
	void ZoomCamera(const FInputActionValue& InputActionValve);

	// Initiate Camera & Character Movement Component
	void StartingViewMode();
	void UpdateCameraModeCPP(const UDA_CameraMode* CameraMode);
	
	UPROPERTY(EditAnywhere, Category="Camera|Zoom", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> ZoomAction = nullptr;
	UPROPERTY(EditAnywhere, Category="Camera|Zoom", meta = (AllowPrivateAccess = "true"))
	float ZoomMax = 1000.f;
	UPROPERTY(EditAnywhere, Category="Camera|Zoom", meta = (AllowPrivateAccess = "true"))
	float ZoomMin = 200.f;
	UPROPERTY(EditAnywhere, Category="Camera|Zoom", meta = (AllowPrivateAccess = "true"))
	float ZoomDefault = 600.f;
	UPROPERTY(EditAnywhere, Category="Camera|Zoom", meta = (AllowPrivateAccess = "true"))
	float ZoomRate = 2.f;

	// Useful pointers
	UPROPERTY()
	ACharacter* CharacterRef = nullptr;
	UPROPERTY()
	UAbilitySystemComponent* CharacterASC = nullptr;
	UPROPERTY()
	UCharacterMovementComponent* CharacterCMC = nullptr;
	UPROPERTY()
	TObjectPtr<USpringArmComponent> SpringArmComponent = nullptr;
	UPROPERTY()
	TObjectPtr<UCameraComponent> CameraComponent = nullptr;
	
	// Helper functions
	bool GetSpringArm();
	bool GetCamera();
	bool GetCharacterASC();
	bool GetCharacterMovementComponent();

	bool CheckCameraMode(FName TagName);
};
