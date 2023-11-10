// Copyright Electronic CAD Monkey [ECM]

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectTypes.h"
#include "GameFramework/Actor.h"
#include "ECMProjectileEffect.generated.h"

struct FGameplayEffectSpecHandle;
class UNiagaraSystem;
class USphereComponent;
class UProjectileMovementComponent;

UCLASS()
class NANOMAGIKA_API AECMProjectileEffect : public AActor
{
	GENERATED_BODY()
	
public:	
	AECMProjectileEffect();

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UProjectileMovementComponent> ProjectileMovement;

	UPROPERTY(BlueprintReadWrite, Category="Effects",meta = (ExposeOnSpawn = true))
	FGameplayEffectSpecHandle DamageEffectSpecHandle;

protected:
	virtual void BeginPlay() override;
	virtual void Destroyed() override;

	UFUNCTION()
	void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY(EditDefaultsOnly, Category="Speed")
	float SpeedInitial = 550.f;
	UPROPERTY(EditDefaultsOnly, Category="Speed")
	float SpeedMax = 550.f;
	UPROPERTY(EditDefaultsOnly, Category="Speed")
	float GravityScale = 0.f;
	
private:
	UPROPERTY(EditDefaultsOnly, Category="Effects")
	float LifeSpan = 15.f;
	
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USphereComponent> Sphere;
	
	UPROPERTY(EditDefaultsOnly, Category="Effects")
	TObjectPtr<UNiagaraSystem> ImpactVFX;

	UPROPERTY(EditDefaultsOnly, Category="Effects")
	TObjectPtr<USoundBase> ImpactSFX;

	UPROPERTY(EditDefaultsOnly, Category="Effects")
	TObjectPtr<USoundBase> LoopingSFX;
	UPROPERTY()
	TObjectPtr<UAudioComponent> LoopingSFXComponent;
	
	bool bHit = false;

	void SpawnFX() const;

};
