// Copyright Electronic CAD Monkey [ECM]

#include "ECMAIController.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "NanoMagika/AbilitySystem/Data/ECMEnemySpecInfo.h"
#include "NanoMagika/Interaction/ECMEnemyInterface.h"

AECMAIController::AECMAIController()
{

	Blackboard = CreateDefaultSubobject<UBlackboardComponent>("Blackboard Component");
	check (Blackboard);
	
	BehaviorTreeComponent = CreateDefaultSubobject<UBehaviorTreeComponent>("Behavior Tree Component");
	check (BehaviorTreeComponent);

}

void AECMAIController::InitializeBB() const
{
	AActor* OwningPawn = GetPawn();
	if ( OwningPawn == nullptr ) return ;
	
	if (OwningPawn->Implements<UECMEnemyInterface>() && Blackboard)
	{
		if ( const UECMEnemySpecInfo* ClassSpec = IECMEnemyInterface::Execute_GetClassSpec(OwningPawn) )
		{
			const FName Name = FName(*ClassSpec->ClassTag.ToString());

			Blackboard->SetValueAsBool(FName("InitComplete"),true);
			Blackboard->SetValueAsName(FName("Class"),Name);
			Blackboard->SetValueAsFloat(FName("RangeMin"), ClassSpec->AttackRange.X);
			Blackboard->SetValueAsFloat(FName("RangeMAX"), ClassSpec->AttackRange.Y);
		}
	}
};