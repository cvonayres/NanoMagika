// Copyright Electronic CAD Monkey [ECM]

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "NanoMagika/Interaction/ECMHightlightInterface.h"
#include "ECMHighlightMeshes.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class NMROSPLUGINRUNTIME_API UECMHighlightMeshes : public UActorComponent, public IECMHightlightInterface
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UECMHighlightMeshes();

	virtual void BeginPlay() override;

	/** Highlight Interface */
	virtual void HighlightActor() override;
	virtual void UnHighlightActor() override;
	/* Highlight Interface */

private:
	UPROPERTY()
	TArray<TObjectPtr<UMeshComponent>> MeshComponents;

	void GetMeshes();
	void SetRenderDepth(bool bState);
};
