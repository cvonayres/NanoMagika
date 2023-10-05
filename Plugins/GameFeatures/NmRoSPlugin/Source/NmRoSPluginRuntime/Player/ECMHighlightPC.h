// Copyright Electronic CAD Monkey [ECM]

#pragma once

#include "CoreMinimal.h"
#include "Components/ControllerComponent.h"
#include "ECMHighlightPC.generated.h"

class IECMHightlightInterface;

UCLASS()
class NMROSPLUGINRUNTIME_API UECMHighlightPC : public UControllerComponent
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;

	UFUNCTION()
	void CursorTrace(const FHitResult& CursorHit);

private:	
	IECMHightlightInterface* LastActor = nullptr;
	IECMHightlightInterface* ThisActor = nullptr;
};
