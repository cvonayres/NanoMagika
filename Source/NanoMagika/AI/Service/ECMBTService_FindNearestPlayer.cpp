// Copyright Electronic CAD Monkey [ECM]

#include "ECMBTService_FindNearestPlayer.h"

#include "AIController.h"
#include "BehaviorTree/BTFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "NanoMagika/ECMGameplayTags.h"
#include "NanoMagika/AbilitySystem/ECMAbilitySystemLibrary.h"
#include "NanoMagika/Character/ECMCharacterBase.h"

// TODO Replace its being call constantly for all enemies
void UECMBTService_FindNearestPlayer::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	const APawn* OwningPawn = AIOwner->GetPawn();

	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(this, AECMCharacterBase::StaticClass(), FoundActors );
	
	AActor* ClosestActor = nullptr;
	float ClosestDistance = TNumericLimits<float>::Max();
	const FGameplayTag PlayerTag = FECMGameplayTags::Get().Character_Type_Player;

	for (AActor* Actor : FoundActors)
	{
		if(IsValid(OwningPawn) && IsValid(Actor) && UECMAbilitySystemLibrary::ActorASCContainsTag(Actor, PlayerTag))
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
