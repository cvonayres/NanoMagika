// Copyright Electronic CAD Monkey [ECM]

#include "ECMHighlightPC.h"
#include "NanoMagika/Player/ECMPlayerController.h"
#include "NmRoSPluginRuntime/Interaction/ECMHightlightInterface.h"

void UECMHighlightPC::BeginPlay()
{
	Super::BeginPlay();
	
	AECMPlayerController* PlayerController = Cast<AECMPlayerController>(GetOwner());
	PlayerController->CursorHitEvent.AddDynamic(this, &UECMHighlightPC::CursorTrace);
}

void UECMHighlightPC::CursorTrace(const FHitResult& CursorHit)
{
	LastActor = ThisActor;

	if(TArray<UActorComponent*> TComponents = CursorHit.GetActor()->GetComponentsByInterface(UECMHightlightInterface::StaticClass()); TComponents.IsEmpty())
	{
		ThisActor = nullptr;
	}
	else
	{
		for (UActorComponent* Component : TComponents)
		{
			ThisActor = Cast<IECMHightlightInterface>(Component);
			break;
		}
	}

	if(LastActor != ThisActor)
	{
		if(LastActor) LastActor->UnHighlightActor();
		if(ThisActor) ThisActor->HighlightActor();
	}
}
