// Copyright Electronic CAD Monkey [ECM]

#pragma once

#include "CoreMinimal.h"
#include "Engine/AssetManager.h"
#include "ECMAssetManager.generated.h"

UCLASS()
class NANOMAGIKA_API UECMAssetManager : public UAssetManager
{
	GENERATED_BODY()

public:

	static UECMAssetManager& Get();

protected:
	virtual void StartInitialLoading() override;
	
};
