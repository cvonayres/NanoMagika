// Copyright Electronic CAD Monkey [ECM]

#pragma once

#include "CoreMinimal.h"
#include "Camera/PlayerCameraManager.h"
#include "ECMPlayerCameraManager.generated.h"

class UInputAction;
class UCameraComponent;
class USpringArmComponent;
struct FInputActionValue;

UCLASS()
class NANOMAGIKA_API AECMPlayerCameraManager : public APlayerCameraManager
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

private:
	// Trying to Get Pawn and Controller
	void TryGetPawnAndController();
    
	FTimerHandle TimerHandle_GetPawnAndController;
	float TimeElapsedTrying = 0.0f;
	float TimeLimitForCheck = 10.0f;  // Your time limit, in seconds.
	float CheckInterval = 0.5f;  // Interval to check, in seconds.

	UPROPERTY()
	APawn* PlayerPawn = nullptr;

	// Initiate Camera & Character Movement Component
	void InitCamera();
	void InitCMC() const;

	UPROPERTY()
	TObjectPtr<USpringArmComponent> SpringArmComponent;
	UPROPERTY()
	TObjectPtr<UCameraComponent> CameraComponent;

	// Initiate Zoom Controls
	void BindInputs();
	void ZoomCamera(const FInputActionValue& InputActionValve);
	
	UPROPERTY(EditAnywhere, Category="Zoom", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> ZoomAction = nullptr;
	UPROPERTY(EditAnywhere, Category="Zoom", meta = (AllowPrivateAccess = "true"))
	float ZoomMax = 1000.f;
	UPROPERTY(EditAnywhere, Category="Zoom", meta = (AllowPrivateAccess = "true"))
	float ZoomMin = 200.f;
	UPROPERTY(EditAnywhere, Category="Zoom", meta = (AllowPrivateAccess = "true"))
	float ZoomDefault = 600.f;
	UPROPERTY(EditAnywhere, Category="Zoom", meta = (AllowPrivateAccess = "true"))
	float ZoomRate = 2.f;
};
