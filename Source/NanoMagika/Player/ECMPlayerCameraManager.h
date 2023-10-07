// Copyright Electronic CAD Monkey [ECM]

#pragma once

#include "CoreMinimal.h"
#include "Camera/PlayerCameraManager.h"
#include "ECMPlayerCameraManager.generated.h"

class UECMInputComponent;
class AECMCharacter;
class UInputAction;
struct FInputActionValue;
class UCameraComponent;
class USpringArmComponent;

UCLASS()
class NANOMAGIKA_API AECMPlayerCameraManager : public APlayerCameraManager
{
	GENERATED_BODY()
	
public:
	void InitPCM(TObjectPtr<USpringArmComponent> SpringArm, TObjectPtr<UCameraComponent> Camera);

	UFUNCTION()
	void BindActionToInput(UECMInputComponent* InputComponentRef);

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY()
	APlayerController* PC = nullptr;
	UPROPERTY()
	TObjectPtr<USpringArmComponent> SpringArmComponent;
	
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
	
	void ZoomCamera(const FInputActionValue& InputActionValve);
	void InitCamera(TObjectPtr<USpringArmComponent> SpringArm, TObjectPtr<UCameraComponent> Camera);
	void InitCMC(AECMCharacter* Character);
	void BindInputs();
};
