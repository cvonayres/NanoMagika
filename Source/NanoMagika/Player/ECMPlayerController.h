// Copyright Electronic CAD Monkey [ECM]

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ECMPlayerController.generated.h"

UENUM()
enum EViewMode
{
	FPV    UMETA(DisplayName = "First Person View"),
	TPV      UMETA(DisplayName = "Third Person View"),
	TDV   UMETA(DisplayName = "Top Down View"),
  };

class UInputMappingContext;
class UInputAction;
class IECMHightlightInterface;
struct FInputActionValue;

UCLASS()
class NANOMAGIKA_API AECMPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AECMPlayerController();

	virtual void PlayerTick(float DeltaTime) override;
	
	UPROPERTY(EditDefaultsOnly, Category="Camera Settings")
	TEnumAsByte<EViewMode> ViewMode = EViewMode::TDV;

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

private:
	UPROPERTY(VisibleAnywhere, Category="Referances")
	class AECMPlayerCameraManager* CameraManager = nullptr;
	
	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputMappingContext> InputContext = nullptr;

	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputAction> MoveAction = nullptr;
	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputAction> ZoomAction = nullptr;
	
	void Move(const FInputActionValue& InputActionValve);
	void ZoomCamera(const FInputActionValue& InputActionValve);

	void CurserTrace();
	IECMHightlightInterface* LastActor = nullptr;
	IECMHightlightInterface* ThisActor = nullptr;
};
