// Copyright Electronic CAD Monkey [ECM]

#pragma once

#include "CoreMinimal.h"
#include "NanoMagika/Player/ECMPlayerController.h"
#include "NmRoSPlayerController.generated.h"

class IECMHightlightInterface;

UCLASS()
class NMROSPLUGINRUNTIME_API ANmRoSPlayerController : public AECMPlayerController
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;
	
	virtual void SetupInputComponent() override;
	
#pragma region AbilityInputTagAction
	virtual void AbilityInputTagPressed(FGameplayTag InputTag) override;

	virtual void AbilityInputTagReleased(FGameplayTag InputTag) override;

	virtual void AbilityInputTagHeld(FGameplayTag InputTag) override;
#pragma endregion AbilityInputTagAction

private:
#pragma region Mouse
	void InitMouse();
#pragma endregion Mouse

#pragma region CursorTrace
	UPROPERTY()
	FHitResult CursorHit = FHitResult();

	void CursorTrace();
#pragma endregion CursorTrace

#pragma region InputActions
	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputAction> MoveAction = nullptr;

	void Move(const FInputActionValue& InputActionValve);
#pragma endregion InputActions

#pragma region ClickToMove
	// Click to move variables
	bool bAutoRunning = false;
	float FollowTime = 0.f;
	FVector CachedDestination = FVector::ZeroVector;
	
	UPROPERTY(EditDefaultsOnly, Category="MoveByCick")
	float ShortPressThreshold = 0.5f;

	UPROPERTY(EditDefaultsOnly, Category="MoveByCick")
	float AutoRunAcceptanceRadius = 50.f;

	bool bTargeting = false;

	UPROPERTY(VisibleAnywhere, Category="MoveByCick")
	TObjectPtr<USplineComponent> Spline;
#pragma endregion  ClickToMove

#pragma region Highlight
	IECMHightlightInterface* LastActor = nullptr;
	IECMHightlightInterface* ThisActor = nullptr;
#pragma endregion  Highlight
};
