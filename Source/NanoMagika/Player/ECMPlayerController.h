// Copyright Electronic CAD Monkey [ECM]

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ECMPlayerController.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FTickSigniture, const FHitResult&, CursorHit);

UENUM()
enum EViewMode
{
	FPV    UMETA(DisplayName = "First Person View"),
	TPV      UMETA(DisplayName = "Third Person View"),
	TDV   UMETA(DisplayName = "Top Down View"),
  };

class UInputMappingContext;
class UInputAction;
struct FInputActionValue;

UCLASS()
class NANOMAGIKA_API AECMPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AECMPlayerController();

	virtual void PreInitializeComponents() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	
	UPROPERTY(EditDefaultsOnly, Category="Camera Settings")
	TEnumAsByte<EViewMode> ViewMode = EViewMode::TDV;

	// Delegate for CursorHit calls
	FTickSigniture CursorHitEvent;

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
	
	void CursorTrace() const;
};
