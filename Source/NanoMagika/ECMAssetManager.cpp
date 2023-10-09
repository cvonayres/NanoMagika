// Copyright Electronic CAD Monkey [ECM]

#include "ECMAssetManager.h"

#include "ECMGameplayTags.h"
#include "AbilitySystemGlobals.h"

UECMAssetManager& UECMAssetManager::Get()
{
	check(GEngine);
	
	UECMAssetManager* ECMAssetManager = Cast<UECMAssetManager>(GEngine->AssetManager);
	return *ECMAssetManager;
}

void UECMAssetManager::StartInitialLoading()
{
	Super::StartInitialLoading();

	// Initiate Gameplay Tags
	FECMGameplayTags::InitNativeGameplayTags();

	// This is required to use Target Data!
	UAbilitySystemGlobals::Get().InitGlobalData();
}
