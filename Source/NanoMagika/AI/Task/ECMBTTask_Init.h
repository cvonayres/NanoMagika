// Copyright Electronic CAD Monkey [ECM]

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlueprintBase.h"
#include "ECMBTTask_Init.generated.h"


UCLASS()
class NANOMAGIKA_API UECMBTTask_Init : public UBTTask_BlueprintBase
{
	GENERATED_BODY()

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

protected:
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="BB Keys")
	FBlackboardKeySelector InitSelector;
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="BB Keys")
	FBlackboardKeySelector ClassSelector;
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="BB Keys")
	FBlackboardKeySelector RangeMin;
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="BB Keys")
	FBlackboardKeySelector RangeMax;

};
