// Copyright Electronic CAD Monkey [ECM]

#pragma once

#include "CoreMinimal.h"
#include "DA_CameraMode.h"
#include "Camera/PlayerCameraManager.h"
#include "ECMPlayerCameraManager.generated.h"

class UCharacterMovementComponent;
class UInputAction;
class UCameraComponent;
class USpringArmComponent;
struct FInputActionValue;

UENUM(BlueprintType)
enum class EStartingCameraMode : uint8
{
	FirstPersonView UMETA(DisplayName = "First Person View"),
	ThirdPersonView UMETA(DisplayName = "Third Person View"),
	TopDownView UMETA(DisplayName = "Top Down View")
};

UCLASS()
class NANOMAGIKA_API AECMPlayerCameraManager : public APlayerCameraManager
{
	GENERATED_BODY()

public:
	// Starting Camera Mode TODO implement gameplay tags instead of ENUM
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Camera")
	EStartingCameraMode StartingCameraMode;
	
	// First Person View
	UFUNCTION(BlueprintCallable, Category="Camera")
	void FirstPersonViewMode() { UpdateCameraMode(FPV_Settings); }
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Camera")
	TObjectPtr<UDA_CameraMode> FPV_Settings;

	// Third Person View
	UFUNCTION(BlueprintCallable, Category="Camera")
	void ThirdPersonViewMode() { UpdateCameraMode(TPV_Settings); }
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Camera")
	TObjectPtr<UDA_CameraMode> TPV_Settings;

	// Top Down View
	UFUNCTION(BlueprintCallable, Category="Camera")
	void TopDownViewMode() { UpdateCameraMode(TDV_Settings); }
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Camera")
	TObjectPtr<UDA_CameraMode> TDV_Settings;

protected:
	virtual void BeginPlay() override;

private:
	// Trying to Get Pawn and Controller
	void TryGetPawnAndController();
    
	FTimerHandle TimerHandle_GetPawnAndController;
	float TimeElapsedTrying = 0.0f;
	float TimeLimitForCheck = 10.0f;  // Your time limit, in seconds.
	float CheckInterval = 0.5f;  // Interval to check, in seconds.

	// Bind Enhanced Inputs TODO add bindings for switching between View modes
	void BindInputs();

	// Zoom Controls
	void ZoomCamera(const FInputActionValue& InputActionValve);

	// Initiate Camera & Character Movement Component
	void UpdateCameraMode(const UDA_CameraMode* CameraMode);
	
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
	APawn* PlayerPawn = nullptr;
	UPROPERTY()
	ACharacter* Character = nullptr;
	UPROPERTY()
	UCharacterMovementComponent* CharacterCMC = nullptr;
	UPROPERTY()
	TObjectPtr<USpringArmComponent> SpringArmComponent = nullptr;
	UPROPERTY()
	TObjectPtr<UCameraComponent> CameraComponent = nullptr;
	
	// Helper functions
	bool GetSpringArm();
	bool GetCamera();
	bool GetCharacter();
	bool GetCharacterMovementComponent();
};
