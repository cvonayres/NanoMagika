// Copyright Electronic CAD Monkey [ECM]

#pragma once

#include "CoreMinimal.h"
#include "UCameraSettingsStrut.h"
#include "Engine/DataAsset.h"
#include "DA_CameraMode.generated.h"


UCLASS()
class NANOMAGIKA_API UDA_CameraMode : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Example")
	FCameraSettings CameraSettings;
	
};
