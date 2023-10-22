// Copyright Electronic CAD Monkey [ECM]

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "NanoMagika/GameplayTagStack.h"
#include "ECMInventoryComponent.generated.h"

//TODO remove to seperate UActor so it can be replicated


enum FAddReturnStatus { Add, AddNew, AddNewItem };

class UECMItemSpecInfo;
/** A single entry in an inventory */
USTRUCT(BlueprintType)
struct FECMInventoryEntry
{
	GENERATED_BODY()

//	UPROPERTY(Replicated)
	UPROPERTY(VisibleAnywhere)
	FGameplayTagStack Item;

	void CreateStack(const UObject* WorldContextObject, FGameplayTag Tag);
	bool CanAddToStack(int32 Count) const;
	void AddToStack(int32 StackCount, int32& Remainder);
	void RemoveItem(int32 StackCount);

	UPROPERTY(VisibleAnywhere)
	FGameplayTagStackContainer ItemStats;

	void AddStat(FGameplayTag Tag, int32 StackCount);
	void RemoveStat(FGameplayTag Tag, int32 StackCount);
	bool ContainsStat(FGameplayTag Tag, int32& StackCount) const;

	UECMItemSpecInfo* GetItemSpec() const { return ItemSpecRef ? ItemSpecRef : nullptr; }

private:
	UPROPERTY(VisibleAnywhere)
	UECMItemSpecInfo* ItemSpecRef = nullptr;
};

/** List of inventory items */
USTRUCT(BlueprintType)
struct FECMInventoryList
{
	GENERATED_BODY()
	FECMInventoryList()	: OwnerComponent(nullptr) {	}
	FECMInventoryList(UActorComponent* InOwnerComponent) : OwnerComponent(InOwnerComponent)	{ }

private:
	UPROPERTY(VisibleAnywhere)
	TArray<FECMInventoryEntry> Entries;

	UPROPERTY(NotReplicated)
	TObjectPtr<UActorComponent> OwnerComponent;

public:
	void Init(const UObject* WorldContextObject);

	void AddEntry(FGameplayTag ItemTagToAdd, int32 StackCount, int32 Passes = 0);

	void RemoveEntry(FGameplayTag ItemTagToRemove, int32 StackCount);

	bool ContainsItem(FGameplayTag ItemTagToCheck) const;

	TArray<FECMInventoryEntry> GetAllItems() const;

private:
	void CreateNewEntry(FGameplayTag ItemTagToAdd);
	
	UPROPERTY()
	const UObject* WorldContextObject;

	UPROPERTY()
	int32 MaxPasses = 10;
	
};
	
UCLASS( Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class NANOMAGIKA_API UECMInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UECMInventoryComponent();

	UFUNCTION(BlueprintCallable)
	void AddItemToInventory(const FGameplayTag ItemTagToAdd, const int32 StackCount);

	UFUNCTION(BlueprintCallable)
	void RemoveItemFromInventory(FGameplayTag ItemTagToRemove, int32 StackCount);

	UFUNCTION(BlueprintCallable)
	bool bDoesInventoryContainItem(FGameplayTag ItemTagToCheck) const;
	
protected:
	virtual void BeginPlay() override;
	
private:
	UPROPERTY(VisibleAnywhere)
	FECMInventoryList InventoryList;
};
