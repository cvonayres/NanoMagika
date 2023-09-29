// Copyright Electronic CAD Monkey [ECM]

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ECMCombatInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UECMCombatInterface : public UInterface
{
	GENERATED_BODY()
};

class NANOMAGIKA_API IECMCombatInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	FORCEINLINE virtual int32 GetPlayerLevel() { return 0;}
};
