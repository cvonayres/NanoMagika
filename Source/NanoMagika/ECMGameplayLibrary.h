// Copyright Electronic CAD Monkey [ECM]

#pragma once

#include "CoreMinimal.h"
#include "ECMGameplayLibrary.generated.h"

UCLASS()
class NANOMAGIKA_API UECMGameplayLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
		
	UFUNCTION(BlueprintCallable, Category="ECMABilitySystemLibrary|GameplayMechanics")
	static void GetLivePlayersWithinRadius(const UObject* WorldContextObject, TArray<AActor*>& OutOverlappingActors, const TArray<AActor*>& ActorsToIgnore, float Radius, const FVector& SphereOrigin);

	UFUNCTION(BlueprintPure, Category="ECMABilitySystemLibrary|GameplayMechanics")
	static bool IsNotFriend(AActor* FirstActor, AActor* SecondActor); 
	
};
