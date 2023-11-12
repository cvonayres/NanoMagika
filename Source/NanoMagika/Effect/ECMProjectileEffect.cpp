// Copyright Electronic CAD Monkey [ECM]


#include "ECMProjectileEffect.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "Components/AudioComponent.h"
#include "Kismet/GameplayStatics.h"
#include "NanoMagika/NanoMagika.h"

// Sets default values
AECMProjectileEffect::AECMProjectileEffect()
{
	PrimaryActorTick.bCanEverTick = false;
	bReplicates = true;

	Sphere = CreateDefaultSubobject<USphereComponent>("Sphere");
	SetRootComponent(Sphere);
	Sphere->SetCollisionObjectType(ECC_Projectile);
	Sphere->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	Sphere->SetCollisionResponseToAllChannels(ECR_Ignore);
	Sphere->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Overlap);
	Sphere->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Overlap);
	Sphere->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>("Projectile Movement");
	ProjectileMovement->InitialSpeed = SpeedInitial;
	ProjectileMovement->MaxSpeed = SpeedMax;
	ProjectileMovement->ProjectileGravityScale = GravityScale;
}

void AECMProjectileEffect::BeginPlay()
{
	Super::BeginPlay();

	SetLifeSpan(LifeSpan);

	Sphere->OnComponentBeginOverlap.AddDynamic(this, &AECMProjectileEffect::OnOverlap);

	LoopingSFXComponent = UGameplayStatics::SpawnSoundAttached(LoopingSFX,GetRootComponent());
}

void AECMProjectileEffect::Destroyed()
{
	if(!bHit && !HasAuthority())
	{
		SpawnFX();
	}
	
	Super::Destroyed();
}

void AECMProjectileEffect::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                               UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if( !DamageEffectSpecHandle.Data.IsValid() || DamageEffectSpecHandle.Data.Get()->GetContext().GetEffectCauser() == OtherActor ) { return; }
	
	if ( !bHit ) 	SpawnFX();
	
	if( HasAuthority() )
	{
		if (UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(OtherActor))
		{
			TargetASC->ApplyGameplayEffectSpecToSelf(*DamageEffectSpecHandle.Data.Get());
		}
		
		Destroy() ;
	}
	else { bHit = true ; }

}

void AECMProjectileEffect::SpawnFX() const
{
	// Spawn Impact VFX
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, ImpactVFX, GetActorLocation());		

	// Spawn Impact SFX
	UGameplayStatics::PlaySoundAtLocation(this, ImpactSFX, GetActorLocation(), FRotator::ZeroRotator);

	if(LoopingSFXComponent) LoopingSFXComponent->Stop();
}