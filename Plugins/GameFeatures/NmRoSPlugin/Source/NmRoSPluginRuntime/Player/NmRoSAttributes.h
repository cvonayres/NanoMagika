// Copyright ECM

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "NmRoSAttributes.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class NMROSPLUGINRUNTIME_API UNmRoSAttributes : public UActorComponent
{
	GENERATED_BODY()

public:	
	UNmRoSAttributes();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
};
