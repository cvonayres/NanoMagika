// Copyright Electronic CAD Monkey [ECM]

#pragma once

#include "CoreMinimal.h"
#include "ActiveGameplayEffectHandle.h"
#include "GameFramework/Actor.h"
#include "ECMEffectActor.generated.h"

class UAbilitySystemComponent;
class UGameplayEffect;

// Enum for Vital Attributes TODO remove and replace with Gameplay Tags
UENUM(BlueprintType)
enum class EEffectType : uint8
{
	Instance      UMETA(DisplayName="Instance"),
	Duration      UMETA(DisplayName="Duration"),
	Infinite      UMETA(DisplayName="Infinte"),
	Periodic      UMETA(DisplayName="Periodic"),	
};


#pragma region Policies
UENUM(BlueprintType)
enum class EEffectApplicationPolicy : uint8
{
	ApplyOnOverlap,
	ApplyOnEndOverlap,
	DoNotApply
};

UENUM(BlueprintType)
enum class EEffectRemovalPolicy : uint8
{
	RemoveOnEndOverlap,
	DoNotRemove
};

UENUM(BlueprintType)
enum class EDestroyPolicy : uint8
{
	ApplyOnOverlap,
	ApplyOnEndOverlap,
	DoNotApply
};
#pragma endregion Policies

UCLASS()
class NANOMAGIKA_API AECMEffectActor : public AActor
{
	GENERATED_BODY()
	
public:	
	AECMEffectActor();

	UPROPERTY(VisibleAnywhere)
	USceneComponent* SceneRoot;
	
protected:
	UFUNCTION(BlueprintCallable)
	void OnOverlap(AActor* TargetActor);
	UFUNCTION(BlueprintCallable)
	void OnEndOverlap(AActor* TargetActor);
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Applied Effects")
	bool bDestroyOnEffectRemoval = false;

#pragma region GameplayEffects
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Applied Effects|Instance")
	TSubclassOf<UGameplayEffect> InstantGameplayEffectClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Applied Effects|Instance")
	EEffectApplicationPolicy InstanceEffectApplicationPolicy = EEffectApplicationPolicy::DoNotApply;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Applied Effects|Duration")
	TSubclassOf<UGameplayEffect> DurationGameplayEffectClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Applied Effects|Duration")
	EEffectApplicationPolicy DurationEffectApplicationPolicy = EEffectApplicationPolicy::DoNotApply;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Applied Effects|Infinite")
	TSubclassOf<UGameplayEffect> InfiniteGameplayEffectClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Applied Effects|Infinite")
	EEffectApplicationPolicy InfiniteEffectApplicationPolicy = EEffectApplicationPolicy::DoNotApply;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Applied Effects|Infinite")
	EEffectRemovalPolicy InfiniteEffectRemovalPolicy = EEffectRemovalPolicy::RemoveOnEndOverlap;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Applied Effects|Periodic")
	TSubclassOf<UGameplayEffect> PeriodicGameplayEffectClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Applied Effects|Periodic")
	EEffectApplicationPolicy PeriodicEffectApplicationPolicy = EEffectApplicationPolicy::DoNotApply;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Applied Effects")
	EDestroyPolicy DestroyPolicy = EDestroyPolicy::DoNotApply;
#pragma endregion GameplayEffects

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Applied Effects")
	float ActorLevel = 1.f;

private:
	void ApplyEffect(UAbilitySystemComponent* TargetASC, TSubclassOf<UGameplayEffect> GameplayEffectClass);
	void ApplyEffectToTarget(AActor* TargetActor, TSubclassOf<UGameplayEffect> GameplayEffectClass);

	void ErrorMessage() const;

	TMap<FActiveGameplayEffectHandle, UAbilitySystemComponent*> ActiveEffectHandles;
};
