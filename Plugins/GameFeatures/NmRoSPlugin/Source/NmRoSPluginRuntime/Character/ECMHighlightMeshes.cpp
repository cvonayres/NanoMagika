// Copyright Electronic CAD Monkey [ECM]

#include "ECMHighlightMeshes.h"

#define CUSTOM_DEPTH_RED 250

UECMHighlightMeshes::UECMHighlightMeshes()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UECMHighlightMeshes::BeginPlay()
{
	Super::BeginPlay();
	
	GetMeshes();
}

/** Highlight Interface */
void UECMHighlightMeshes::HighlightActor() { SetRenderDepth(true); }

void UECMHighlightMeshes::UnHighlightActor() { SetRenderDepth(false); }
/** Highlight Interface */

void UECMHighlightMeshes::GetMeshes()
{
	TArray<TObjectPtr<USkeletalMeshComponent>> SkeletalMeshComponents;
	GetOwner()->GetComponents<USkeletalMeshComponent>(SkeletalMeshComponents);
	
	TArray<TObjectPtr<UStaticMeshComponent>> StaticMeshComponents;
	GetOwner()->GetComponents<UStaticMeshComponent>(StaticMeshComponents);

	// Merge arrays
	MeshComponents.Append(SkeletalMeshComponents);
	MeshComponents.Append(StaticMeshComponents);
	
	if(MeshComponents.IsEmpty()) return;
	
	for(const auto Mesh : MeshComponents)
	{
		Mesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Block);
		Mesh->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);
	}
}

void UECMHighlightMeshes::SetRenderDepth(const bool bState)
{
	if(MeshComponents.IsEmpty()) return;

	for(const  TObjectPtr<UMeshComponent> Mesh : MeshComponents)
	{
		Mesh->SetRenderCustomDepth(bState);
	}
}
