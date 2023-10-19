// Copyright Electronic CAD Monkey [ECM]

#include "ECMAIController.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

AECMAIController::AECMAIController()
{
	Blackboard = CreateDefaultSubobject<UBlackboardComponent>("Blackboard Component");
	check (Blackboard);
	
	BehaviorTreeComponent = CreateDefaultSubobject<UBehaviorTreeComponent>("Behavior Tree Component");
	check (BehaviorTreeComponent);
}
