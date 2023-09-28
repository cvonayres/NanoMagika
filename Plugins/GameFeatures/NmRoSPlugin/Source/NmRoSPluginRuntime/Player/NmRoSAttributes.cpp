// Copyright ECM

#include "NmRoSAttributes.h"

// Sets default values for this component's properties
UNmRoSAttributes::UNmRoSAttributes()
{
	PrimaryComponentTick.bCanEverTick = false;

}

// Called when the game starts
void UNmRoSAttributes::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void UNmRoSAttributes::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
}

