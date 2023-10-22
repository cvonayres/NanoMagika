// Copyright Electronic CAD Monkey [ECM]

#include "ECMInventoryComponent.h"

#include "Kismet/GameplayStatics.h"
#include "NanoMagika/Game/ECMGameMode.h"
#include "NanoMagika/Inventory/Data/ECMItemClassInfo.h"
#include "NanoMagika/Inventory/Data/ECMItemSpecInfo.h"

#pragma region List_Item_Functions
void FECMInventoryEntry::CreateStack(const UObject* WorldContextObject, FGameplayTag TagIN)
{
	if( !IsValid(WorldContextObject) || !TagIN.IsValid() ) return ;
	
	Item.Tag = TagIN;
	Item.StackCount = 1;
	
	if(const AECMGameMode* GameMode = Cast<AECMGameMode>(UGameplayStatics::GetGameMode(WorldContextObject)))
	{
		ItemSpecRef = GameMode->ItemClassInfo->GetItemDefaultInfo(TagIN);	
	}
}
//BUG Creates empty objects if world context is empty
bool FECMInventoryEntry::CanAddToStack(int32 Count) const
{
	if (ItemSpecRef->GetItemStackPolicy() == EItemStackPolicy::None)
	{
		return false;
	}
	
	if (ItemSpecRef->GetItemStackPolicy() == EItemStackPolicy::Capped)
	{
		const int32 SpaceLeft = ItemSpecRef->GetItemStackSize() - Item.StackCount;

		if (SpaceLeft <= 0)
		{
			return false;
		}
		else
		{
			return true;
		}
	}
	
	if (ItemSpecRef->GetItemStackPolicy() == EItemStackPolicy::Uncapped)
	{
		return true;
	}
	
	return false;
}

void FECMInventoryEntry::AddToStack(int32 StackCount, int32& Remainder)
{
	if(StackCount < 1) return;
		
	if (ItemSpecRef->GetItemStackPolicy() == EItemStackPolicy::Capped)
	{
		const int32 SpaceLeft = ItemSpecRef->GetItemStackSize() - Item.StackCount;

		if (SpaceLeft >= StackCount)
		{
			Item.AddCount(StackCount);
			Remainder = 0;
		}
		else
		{
			Item.AddCount(SpaceLeft);
			Remainder = StackCount - SpaceLeft;
		}	
	}
	
	if (ItemSpecRef->GetItemStackPolicy() == EItemStackPolicy::Uncapped)
	{
		Item.AddCount(StackCount);
		Remainder = 0;
	}
}

void FECMInventoryEntry::RemoveItem(int32 StackCount)
{
	unimplemented();
}

#pragma endregion List_Item_Functions

#pragma region List_Item_Stat_Functions
// Add Stat Tag to item
void FECMInventoryEntry::AddStat(FGameplayTag Tag, int32 StackCount)
{
	ItemStats.AddStack(Tag, StackCount);
}

// Remove Stat Tag to item
void FECMInventoryEntry::RemoveStat(FGameplayTag Tag, int32 StackCount)
{
	ItemStats.RemoveStack(Tag, StackCount);
}

// Check if Stat Tag to is in item and get qty
bool FECMInventoryEntry::ContainsStat(FGameplayTag Tag, int32& StackCount) const
{
	if(ItemStats.ContainsTag(Tag))
	{
		StackCount = ItemStats.GetStackCount(Tag);
	}
	return ItemStats.ContainsTag(Tag);
}
#pragma endregion List_Item_Stat_Functions

#pragma region List_Functions
void FECMInventoryList::Init(const UObject* WorldContextObjectIN)
{
	WorldContextObject = WorldContextObjectIN;
}

void FECMInventoryList::AddEntry(const FGameplayTag ItemTagToAdd, const int32 Count, int32 Passes)
{
	if ( !ItemTagToAdd.IsValid() || Passes > MaxPasses) return ;

	int32 Remainder = Count;
	
	for (auto& Entry : Entries)
	{
		if (Entry.Item.Tag == ItemTagToAdd && Entry.CanAddToStack(Count))
		{
			Entry.AddToStack(Count, Remainder);
			break;
		}
	}
	
	if (Remainder > 0 )
	{
		Passes++;
		FECMInventoryEntry Entry;
		Entry.CreateStack(WorldContextObject, ItemTagToAdd);
		Entries.Add(Entry);
		Remainder--;
		AddEntry(ItemTagToAdd, Remainder, Passes);
	}
}

void FECMInventoryList::CreateNewEntry(const FGameplayTag ItemTagToAdd)
{

}

void FECMInventoryList::RemoveEntry(FGameplayTag ItemTagToRemove, int32 StackCount)
{
	if ( !ItemTagToRemove.IsValid() || !ContainsItem(ItemTagToRemove)) return;

	for (auto Entry : Entries)
	{
		Entry.RemoveItem(StackCount);
		break;
	}
}

bool FECMInventoryList::ContainsItem(FGameplayTag ItemTagToCheck) const
{
	unimplemented();
	return false;
}

TArray<FECMInventoryEntry> FECMInventoryList::GetAllItems() const
{
	return Entries;
}

#pragma endregion List_Functions

UECMInventoryComponent::UECMInventoryComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	
}

void UECMInventoryComponent::AddItemToInventory(const FGameplayTag ItemTagToAdd, const int32 StackCount)
{
	 InventoryList.AddEntry(ItemTagToAdd, StackCount, 0);
}

void UECMInventoryComponent::RemoveItemFromInventory(FGameplayTag ItemTagToRemove, int32 StackCount)
{
	unimplemented();
}

bool UECMInventoryComponent::bDoesInventoryContainItem(FGameplayTag ItemTagToCheck) const
{
	unimplemented();
	return false;
}

void UECMInventoryComponent::BeginPlay()
{
	Super::BeginPlay();
	
	InventoryList.Init(GetOwner());

}
