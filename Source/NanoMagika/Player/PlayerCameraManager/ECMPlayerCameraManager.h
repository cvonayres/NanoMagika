// Copyright Electronic CAD Monkey [ECM]

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "InputActionValue.h"
#include "Camera/PlayerCameraManager.h"
#include "ECMPlayerCameraManager.generated.h"

class UDA_CameraMode;
class UInputAction;
class USpringArmComponent;
class UCameraComponent;

USTRUCT(BlueprintType)
struct FCameraTags
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, Category = "Camera|Defaults")
	FGameplayTag InputTag_CameraMode;
	
	UPROPERTY(EditDefaultsOnly, Category = "Camera|Defaults")
	TMap<FGameplayTag, FGameplayTag> InputToDefaultMapping;
	
	UPROPERTY(EditDefaultsOnly, Category = "Camera|Defaults")
	TMap<FGameplayTag, TObjectPtr<UDA_CameraMode>> TagToCameraSettingMapping;

	FGameplayTag GetCameraTagFromInputTag (const FGameplayTag& InputTag)
	{
		if ( InputTag.IsValid() )
		{
			return  *InputToDefaultMapping.Find(InputTag);
		}
		return	FGameplayTag();
	}
	
	TObjectPtr<UDA_CameraMode> GetSettingFromTag (const FGameplayTag& CameraTag)
	{
		if ( CameraTag.IsValid() )
		{
			return	*TagToCameraSettingMapping.Find(CameraTag);
		}
		return nullptr;
	}
};

USTRUCT(BlueprintType)
struct FZoomSettings
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category="Camera|Zoom", meta = (AllowPrivateAccess = "true"))
	float ZoomMax;
	UPROPERTY(EditAnywhere, Category="Camera|Zoom", meta = (AllowPrivateAccess = "true"))
	float ZoomMin;
	UPROPERTY(EditAnywhere, Category="Camera|Zoom", meta = (AllowPrivateAccess = "true"))
	float ZoomDefault;
	UPROPERTY(EditAnywhere, Category="Camera|Zoom", meta = (AllowPrivateAccess = "true"))
	float ZoomRate;
	
	FZoomSettings()
	{
		ZoomMax = 1000.f;
		ZoomMin = 200.f;
		ZoomDefault = 800.f;
		ZoomRate = 2.f;
	}
};

UCLASS()
class NANOMAGIKA_API AECMPlayerCameraManager : public APlayerCameraManager
{
	GENERATED_BODY()

public:
	UFUNCTION(Category="Camera")
	void InitPCM(const ACharacter* Character);
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Camera")
	FCameraTags CameraTags;
	
protected:
	/** Zoom */
	void ZoomCamera(const FInputActionValue& InputActionValve);
	
	UPROPERTY(EditAnywhere, Category="Camera|Zoom")
	TObjectPtr<UInputAction> ZoomAction = nullptr;

	UPROPERTY(EditAnywhere, Category="Camera|Zoom")
	FZoomSettings ZoomSettings;
	/* Zoom **/

	// Useful pointers
	UPROPERTY(BlueprintReadOnly, Category="Camera")
	ACharacter* CharacterRef = nullptr;
	
	UPROPERTY(BlueprintReadOnly, Category="Camera")
	TObjectPtr<USpringArmComponent> SpringArmComponent = nullptr;
	
	UPROPERTY(BlueprintReadOnly, Category="Camera")
	TObjectPtr<UCameraComponent> CameraComponent = nullptr;

	UPROPERTY(BlueprintReadOnly, Category="Camera")
	bool bCanCheckForFade = false;
	
private:
	// Initiate Camera & Character Movement Component
	void StartingViewMode();
	
	// Bind Enhanced Inputs
	void BindInputs();

	// React to Bound Inputs
	virtual void AbilityInputTagPressed(FGameplayTag InputTag);

	// Update Camera Mode based on Default or Input buttons
	void UpdateCameraMode(TObjectPtr<UDA_CameraMode> CameraDA);
	
	// Helper functions
	bool IsSpringArmValid();
	
	bool IsCameraValid();
};
