// Copyright Electronic CAD Monkey [ECM]

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "ECMItemSpecInfo.generated.h"

UENUM(BlueprintType)
enum class EItemStackPolicy : uint8
{
	None UMETA(DisplayName = "None"),
	Capped UMETA(DisplayName = "Capped"),
	Uncapped UMETA(DisplayName = "Uncapped")
};

UCLASS()
class NANOMAGIKA_API UECMItemSpecInfo : public UDataAsset
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintGetter, Category="Description")
	FText  GetItemName() const {return Name ; };

	UFUNCTION(BlueprintGetter, Category="Description")
	FText  GetItemDescription() const {return Description ; };

	UFUNCTION(BlueprintGetter, Category="Description")
	UTexture2D* GetItemIcon() const {return Icon ; };

	UFUNCTION(BlueprintGetter, Category="Description")
	EItemStackPolicy GetItemStackPolicy() const {return StackPolicy ; };
	
	UFUNCTION(BlueprintGetter, Category="Description")
	int32 GetItemStackSize() const {return StackSize ; };
	
private:
	
	UPROPERTY(EditDefaultsOnly, Category="Tags",  meta = (AllowPrivateAccess = "true"))
	FGameplayTag ClassTag;

	UPROPERTY(EditDefaultsOnly, Category="Description", meta = (AllowPrivateAccess = "true"))
	FText  Name;

	UPROPERTY(EditDefaultsOnly, Category="Description", meta = (AllowPrivateAccess = "true"))
	FText  Description;
	
	UPROPERTY(EditDefaultsOnly, Category="Icon", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UTexture2D> Icon;

	UPROPERTY(EditDefaultsOnly, Category="Stack", meta = (AllowPrivateAccess = "true"))
	EItemStackPolicy StackPolicy = EItemStackPolicy::None;

	UPROPERTY(EditDefaultsOnly, Category="Stack", meta = (AllowPrivateAccess = "true"))
	int32 StackSize = 0;
	
};
