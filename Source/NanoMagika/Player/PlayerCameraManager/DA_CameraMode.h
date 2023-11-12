// Copyright Electronic CAD Monkey [ECM]

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "DA_CameraMode.generated.h"

USTRUCT(BlueprintType)
struct FCameraTagsCameraSettings
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Camera Tags")
	FGameplayTag GameplayTag;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Camera Tags")
	FGameplayTag TagToRemove1;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Camera Tags")
	FGameplayTag TagToRemove2;

	FCameraTagsCameraSettings()
	{
		GameplayTag = FGameplayTag();
		TagToRemove1 = FGameplayTag();
		TagToRemove2 = FGameplayTag();
	}
};

USTRUCT(BlueprintType)
struct FSpringArmCameraSettings
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="SpringArm")
	FVector Location;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="SpringArm")
	FRotator Rotation;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="SpringArm")
	float TargetArmLength;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="SpringArm")
	bool UsePawnControlRotation;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="SpringArm")
	bool InheritPitch;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="SpringArm")
	bool InheritRoll;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="SpringArm")
	bool InheritYaw;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="SpringArm")
	bool EnableCameraLag;

	FSpringArmCameraSettings()
	{
		Location = FVector(0.f,0.f,0.f);
		Rotation = FRotator(-45.f,0.f,0.f);
		TargetArmLength = 800.f;
		UsePawnControlRotation = false;
		InheritPitch = false;
		InheritRoll = false;
		InheritYaw = false;
		EnableCameraLag = true;	
	}
};

USTRUCT(BlueprintType)
struct FCameraSettings
{
	GENERATED_BODY()

	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Camera")
	bool UsePawnControlRotation;

	FCameraSettings()
	{
		UsePawnControlRotation = false;
	}
};

USTRUCT(BlueprintType)
struct FCharacterCameraSettings
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Character")
	bool UseControllerRotationPitch;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Character")
	bool UseControllerRotationRoll;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Character")
	bool UseControllerRotationYaw;

	FCharacterCameraSettings()
	{
		UseControllerRotationPitch = false;
		UseControllerRotationRoll = false;
		UseControllerRotationYaw = false;	}
};

USTRUCT(BlueprintType)
struct FCharacterMCCameraSettings
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="CharacterMC")
	bool bOrientRotationToMovement;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="CharacterMC")
	FRotator RotationRate;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="CharacterMC")
	bool ConstrainToPlane;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="CharacterMC")
	bool SnapToPlaneAtStart;
	
	FCharacterMCCameraSettings()
	{
		bOrientRotationToMovement = true;
		RotationRate = FRotator(0.f, 400.f,0.f);
		ConstrainToPlane = true;
		SnapToPlaneAtStart = true;
	}
};

UCLASS()
class NANOMAGIKA_API UDA_CameraMode : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName Name = FName("");

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Default")
	FCameraTagsCameraSettings CameraTags = FCameraTagsCameraSettings();
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Default")
	FSpringArmCameraSettings SpringArmSettings = FSpringArmCameraSettings() ;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Default")
	FCameraSettings Camera = FCameraSettings();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Default")
	FCharacterCameraSettings Character = FCharacterCameraSettings();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Default")
	FCharacterMCCameraSettings CharacterMC = FCharacterMCCameraSettings();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Chaacter")
	bool bCanCheckForFadeActors = false;
};
