// Copyright Electronic CAD Monkey [ECM]

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlueprintBase.h"
#include "ECMBTService_FindNearestPlayer.generated.h"


UCLASS()
class NANOMAGIKA_API UECMBTService_FindNearestPlayer : public UBTService_BlueprintBase
{
	GENERATED_BODY()

protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="BB Keys")
	FBlackboardKeySelector TargetActorSelector;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="BB Keys")
	FBlackboardKeySelector DistanceToTargetSelector;

	
};
