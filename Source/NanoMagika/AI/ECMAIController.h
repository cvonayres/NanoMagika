// Copyright Electronic CAD Monkey [ECM]

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "ECMAIController.generated.h"


class UBehaviorTreeComponent;

UCLASS()
class NANOMAGIKA_API AECMAIController : public AAIController
{
	GENERATED_BODY()

public:
	AECMAIController();

protected:
	UPROPERTY()
	TObjectPtr<UBehaviorTreeComponent> BehaviorTreeComponent;
	
};

