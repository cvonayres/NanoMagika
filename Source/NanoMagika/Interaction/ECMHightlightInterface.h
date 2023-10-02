// Copyright Electronic CAD Monkey [ECM]

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ECMHightlightInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UECMHightlightInterface : public UInterface
{
	GENERATED_BODY()
};

class NANOMAGIKA_API IECMHightlightInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
	public:
	virtual void HighlightActor() = 0;
	virtual void UnHighlighActor() = 0;
};
