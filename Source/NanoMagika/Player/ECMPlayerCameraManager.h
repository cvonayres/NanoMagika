// Copyright Electronic CAD Monkey [ECM]

#pragma once

#include "CoreMinimal.h"
#include "Camera/PlayerCameraManager.h"
#include "ECMPlayerCameraManager.generated.h"

UENUM()
enum EVectorDirection
{
	Fwd		  UMETA(DisplayName = "Forward Vector"),
	Right     UMETA(DisplayName = "Right Vector"),
	Up		  UMETA(DisplayName = "Up Vector"),
  };

class AECMPlayerController;

UCLASS()
class NANOMAGIKA_API AECMPlayerCameraManager : public APlayerCameraManager
{
	GENERATED_BODY()
	
public:
	AECMPlayerCameraManager();

	void UpdateZoom(float valve);
	void InitCamera();
	
protected:
	virtual void BeginPlay() override;

	// Camera Functions
	UFUNCTION(BlueprintPure)
	FVector GetUpdatedLocation() const;
	UFUNCTION(BlueprintPure)
	FRotator GetUpdatedRotation() const;

	// View Settings
	UPROPERTY(EditDefaultsOnly, Category="Camera Settings|FirstPersonView")
	FVector FPVOffset;
	UPROPERTY(EditAnywhere, Category="Camera Settings|FirstPersonView")
	FRotator FPVRotation;
	UPROPERTY(EditDefaultsOnly, Category="Camera Settings|ThirdPersonView")
	FVector TPVOffset;
	UPROPERTY(EditAnywhere, Category="Camera Settings|ThirdPersonView")
	FRotator TPVRotation;
	UPROPERTY(EditDefaultsOnly, Category="Camera Settings|TopDownView")
	FVector TDVOffset;
	UPROPERTY(EditAnywhere, Category="Camera Settings|TopDownView")
	FRotator TDVRotation;

	// Zoom Controls
	UPROPERTY(EditAnywhere, Category="Camera Settings|Zoom")
	UCurveFloat* ZoomCurve;
	UPROPERTY(EditAnywhere, Category="Camera Settings|Zoom")
	FVector ZoomMAX;
	UPROPERTY(EditAnywhere, Category="Camera Settings|Zoom")
	FVector ZoomMIN;
	UPROPERTY(BlueprintReadOnly, Category="Camera Settings|Zoom")
	FVector Test;
private:
	//Referances
	UPROPERTY(VisibleAnywhere, Category="Referances")
	TObjectPtr<AECMPlayerController> Controller;
	UPROPERTY(VisibleAnywhere, Category="Referances")
	TObjectPtr<APawn>ControlledPawn;

	//Private Variables
	FVector VOffset;
	FRotator ROffset;
	
	//Private functions
	FVector GetCameraVector(EVectorDirection Direction) const;
};
