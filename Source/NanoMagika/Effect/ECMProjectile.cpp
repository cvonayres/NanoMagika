// Copyright Electronic CAD Monkey [ECM]


#include "ECMProjectile.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "Components/AudioComponent.h"
#include "Kismet/GameplayStatics.h"
#include "NanoMagika/NanoMagika.h"

// Sets default values
AECMProjectile::AECMProjectile()
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

void AECMProjectile::BeginPlay()
{
	Super::BeginPlay();

	SetLifeSpan(LifeSpan);

	Sphere->OnComponentBeginOverlap.AddDynamic(this, &AECMProjectile::OnOverlap);

	LoopingSFXComponent = UGameplayStatics::SpawnSoundAttached(LoopingSFX,GetRootComponent());
}

void AECMProjectile::Destroyed()
{
	if(!bHit && !HasAuthority())
	{
		SpawnFX();
	}
	
	Super::Destroyed();
}

void AECMProjectile::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                               UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(!DamageEffectSpecHandle.Data.IsValid())
	{
		return;
	}

	if (DamageEffectSpecHandle.Data.Get()->GetContext().GetEffectCauser() == OtherActor)
	{
		return;
	}

	if (!bHit) 	SpawnFX();
	
	if(HasAuthority())
	{
		if (UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(OtherActor))
		{
			TargetASC->ApplyGameplayEffectSpecToSelf(*DamageEffectSpecHandle.Data.Get());
		}
		
		Destroy() ;
	}
	else { bHit = true ; }

}

void AECMProjectile::SpawnFX() const
{
	// Spawn Impact VFX
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, ImpactVFX, GetActorLocation());		

	// Spawn Impact SFX
	UGameplayStatics::PlaySoundAtLocation(this, ImpactSFX, GetActorLocation(), FRotator::ZeroRotator);

	if(LoopingSFXComponent) LoopingSFXComponent->Stop();
}