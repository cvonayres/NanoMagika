// Copyright Electronic CAD Monkey [ECM]

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "UObject/Interface.h"
#include "ECMEnemyInterface.generated.h"

class UECMCharacterClassInfo;
class UECMEnemySpecInfo;

// This class does not need to be modified.
UINTERFACE(MinimalAPI, BlueprintType)
class UECMEnemyInterface : public UInterface
{
	GENERATED_BODY()
};

class NANOMAGIKA_API IECMEnemyInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	FGameplayTag GetEnemyTag();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	UECMCharacterClassInfo* GetClassInfo() ;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	UECMEnemySpecInfo* GetClassSpec() ;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	float GetAttackRadius() ;
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	TMap<FGameplayTag, UAnimMontage*> GetAttackMontages();



};
