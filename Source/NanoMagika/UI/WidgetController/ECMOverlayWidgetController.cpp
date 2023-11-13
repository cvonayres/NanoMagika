// Copyright Electronic CAD Monkey [ECM]

#include "ECMOverlayWidgetController.h"
#include "NanoMagika/AbilitySystem/ECMAbilitySystemComponent.h"
#include "NanoMagika/AbilitySystem/Attributes/ECMAttributeSet.h"
#include "NanoMagika/AbilitySystem/Data/ECMAbilityInformation.h"
#include "NanoMagika/AbilitySystem/Data/ECMLevelUpInformation.h"
#include "NanoMagika/Player/PlayerState/ECMPlayerState.h"

// Broadcast when Attribute change
void UECMOverlayWidgetController::BroadcastInitialValues()
{
	const UECMAttributeSet* ECMAttributeSet = CastChecked<UECMAttributeSet>(AttributeSet);

	OnVitalityMatrixChangedDelegate.Broadcast(ECMAttributeSet->GetVitalityMatrix());
	OnVMCapacityChangedDelegate.Broadcast(ECMAttributeSet->GetVMCapacity());
	OnArcaneReservoirChangeDelegate.Broadcast(ECMAttributeSet->GetArcaneReservoir());
	OnARCapacityChangedDelegate.Broadcast(ECMAttributeSet->GetARCapacity());
}

// Bind Listeners for Attribute change
void UECMOverlayWidgetController::BindCallbacksToDependencies()
{
	AECMPlayerState* ECMPlayerState = CastChecked<AECMPlayerState>(PlayerState);
	ECMPlayerState->OnXPChangedDelegate.AddUObject(this, &UECMOverlayWidgetController::OnXPChanged);

	const UECMAttributeSet* ECMAttributeSet = CastChecked<UECMAttributeSet>(AttributeSet);
	
	// Bind vital attributes
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(ECMAttributeSet->GetVitalityMatrixAttribute()).AddLambda(
		[this](const FOnAttributeChangeData &Data)	{ OnVitalityMatrixChangedDelegate.Broadcast(Data.NewValue);});
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(ECMAttributeSet->GetVMCapacityAttribute()).AddLambda(
		[this](const FOnAttributeChangeData &Data)	{ OnVMCapacityChangedDelegate.Broadcast(Data.NewValue);});

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(ECMAttributeSet->GetArcaneReservoirAttribute()).AddLambda(
	[this](const FOnAttributeChangeData &Data)	{ OnArcaneReservoirChangeDelegate.Broadcast(Data.NewValue);});
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(ECMAttributeSet->GetARCapacityAttribute()).AddLambda(
[this](const FOnAttributeChangeData &Data)	{ OnARCapacityChangedDelegate.Broadcast(Data.NewValue);});

	UECMAbilitySystemComponent*	ECMASC = Cast<UECMAbilitySystemComponent>(AbilitySystemComponent);
	if ( ECMASC == nullptr ) return;

	// Bind Abilities Info
	if ( ECMASC->bStartupAbiltiesGiven )
	{
		OnInitializedStartupAbilities(ECMASC);
	}
	else
	{
		ECMASC->AbilitiesGivenDelegate.AddUObject( this, &UECMOverlayWidgetController::OnInitializedStartupAbilities) ;
	}
	
	// Bind Message Widget Row
	ECMASC->EffectAssetTagsDelegate.AddLambda(
	[this](const FGameplayTagContainer& AssetTags)
		{
			for(const FGameplayTag& Tag : AssetTags)
			{
				// Only look for row from data table if tag has message
				FGameplayTag MessageTag = FGameplayTag::RequestGameplayTag(FName("Message.UI"));
				if(Tag.MatchesTag(MessageTag))
				{
					const FUIWidgetRow* Row = GetDataTableRowByTag<FUIWidgetRow>(MessageWidgetDataTable, Tag);
					MessageWidgetRowDelegate.Broadcast(*Row);
				}
			}
		}
		);
}

void UECMOverlayWidgetController::OnInitializedStartupAbilities(UECMAbilitySystemComponent*	ASC) const
{
	if (!ASC->bStartupAbiltiesGiven) return;

	FForEachAbility BroadcastDelegate;
	BroadcastDelegate.BindLambda([this, ASC](const FGameplayAbilitySpec& AbilitySpec)
	{
		//TODO need a way to figure out the ability tag for a given ability spec.
		FECMAbilityInfo Info = AbilityInfo->FindAbilityInfoForTag(ASC->GetAbilityTagFromSpec(AbilitySpec));
		Info.InputTag = ASC->GetInputTagFromSpec(AbilitySpec);
		AbiltyInfoDelegate.Broadcast(Info);
	});
	ASC->ForEachAbilitiy(BroadcastDelegate);
}

void UECMOverlayWidgetController::OnXPChanged(int32 NewXP) const
{
	const AECMPlayerState* ECMPlayerState = CastChecked<AECMPlayerState>(PlayerState);
	const UECMLevelUpInformation* LevelUpInformation = ECMPlayerState->LevelUpInfo;
	checkf(LevelUpInformation, TEXT("Unable to find Level up info, Please fill out ECMPlayerState Blueprint"));

	const int32 Level = LevelUpInformation->FindLevelForXP(NewXP);
	const int32 MaxLevel = LevelUpInformation->LevelUpInformation.Num();

	if ( Level <= MaxLevel && Level >0 )
	{
		const int32 LevelUpRequirement	= LevelUpInformation->LevelUpInformation[Level].LevelUpThreshold;
		const int32 PreviousLevelUpRequirement	= LevelUpInformation->LevelUpInformation[Level-1].LevelUpThreshold;

		const int32 DeltaLevelRequirement = LevelUpRequirement - PreviousLevelUpRequirement;
		const int32 XPForThisLevel = NewXP - PreviousLevelUpRequirement;

		const float XPBarPercent = static_cast<float>(XPForThisLevel) / static_cast<float>(DeltaLevelRequirement);

		OnXPPercentChangeDelegate.Broadcast(XPBarPercent);
	}
}
