// Copyright Electronic CAD Monkey [ECM]

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "DA_CameraMode.generated.h"

USTRUCT(BlueprintType)
struct FCameraSettings
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName Name = FName("");

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGameplayTag GameplayTag = FGameplayTag();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="SpringArm")
	FVector Location = FVector(0.f,0.f,0.f);
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="SpringArm")
	FRotator Rotation = FRotator(-45.f,0.f,0.f);
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="SpringArm")
	float TargetArmLength = 600.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="SpringArm")
	bool SpringArmUsePawnControlRotation = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="SpringArm")
	bool InheritPitch = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="SpringArm")
	bool InheritRoll = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="SpringArm")
	bool InheritYaw = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="SpringArm")
	bool EnableCameraLag = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Camera")
	bool CameraUsePawnControlRotation = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Character")
	bool UseControllerRotationPitch = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Character")
	bool UseControllerRotationRoll = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Character")
	bool UseControllerRotationYaw = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="CharacterMC")
	bool bOrientRotationToMovement = true;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Chaacter")
	FRotator RotationRate = FRotator(0.f, 400.f,0.f);
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Chaacter")
	bool ConstrainToPlane = true;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Chaacter")
	bool SnapToPlaneAtStart = true;
};

UCLASS()
class NANOMAGIKA_API UDA_CameraMode : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Example")
	FCameraSettings CameraSettings;
	
};
