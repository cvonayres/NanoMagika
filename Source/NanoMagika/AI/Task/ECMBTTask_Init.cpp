// Copyright Electronic CAD Monkey [ECM]

#include "ECMBTTask_Init.h"

#include "AbilitySystemComponent.h"
#include "AIController.h"
#include "BehaviorTree/BTFunctionLibrary.h"
#include "NanoMagika/ECMGameplayTags.h"
#include "NanoMagika/AbilitySystem/ECMAbilitySystemLibrary.h"
#include "NanoMagika/AbilitySystem/Data/ECMEnemySpecInfo.h"
#include "NanoMagika/Character/ECMEnemy.h"

EBTNodeResult::Type UECMBTTask_Init::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	AActor* OwningPawn = AIOwner->GetPawn();
	// Check if Enemy Class
	if (const AECMEnemy* Enemy = Cast<AECMEnemy>(OwningPawn); Enemy == nullptr) return EBTNodeResult::Failed;

	if ( AActor* Actor = AIOwner->GetPawn(); Actor->Implements<UECMEnemyInterface>() )
	{
		if (const UECMEnemySpecInfo* ClassSpec = IECMEnemyInterface::Execute_GetClassSpec(Actor); ClassSpec != nullptr)
		{
			const FName Name = FName(*ClassSpec->ClassTag.ToString());
			
			UBTFunctionLibrary::SetBlackboardValueAsBool(this,InitSelector, true);
			UBTFunctionLibrary::SetBlackboardValueAsName(this,ClassSelector, Name);
			UBTFunctionLibrary::SetBlackboardValueAsFloat(this,RangeMin, ClassSpec->AttackRange.X);
			UBTFunctionLibrary::SetBlackboardValueAsFloat(this,RangeMax, ClassSpec->AttackRange.Y);

			return EBTNodeResult::Succeeded;
		}
	}
	return EBTNodeResult::Failed;
}
