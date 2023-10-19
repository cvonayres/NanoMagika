// Copyright Electronic CAD Monkey [ECM]

#include "ECMBTService_FindNearestPlayer.h"

#include "AbilitySystemComponent.h"
#include "AIController.h"
#include "BehaviorTree/BTFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "NanoMagika/ECMGameplayTags.h"
#include "NanoMagika/Character/ECMCharacterBase.h"


void UECMBTService_FindNearestPlayer::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	const APawn* OwningPawn = AIOwner->GetPawn();

	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(this, AECMCharacterBase::StaticClass(), FoundActors );
	const FGameplayTag PlayerTag = FECMGameplayTags::Get().Character_Type_Player;

	AActor* ClosestActor = nullptr;
	float ClosestDistance = TNumericLimits<float>::Max();

	for (AActor* Actor : FoundActors)
	{
		const AECMCharacterBase* Character = Cast<AECMCharacterBase>(Actor);
    
		if(IsValid(OwningPawn) && IsValid(Character) && Character->GetAbilitySystemComponent()->HasMatchingGameplayTag(PlayerTag))
		{
			if (const float Distance = OwningPawn->GetDistanceTo(Actor); Distance < ClosestDistance)
			{
				ClosestActor = Actor;
				ClosestDistance = Distance;
			}
		}
	}
	
	if(ClosestActor != nullptr)
	{
		UBTFunctionLibrary::SetBlackboardValueAsObject(this, TargetActorSelector, ClosestActor);
		UBTFunctionLibrary::SetBlackboardValueAsFloat(this, DistanceToTargetSelector, ClosestDistance);
	}
}
