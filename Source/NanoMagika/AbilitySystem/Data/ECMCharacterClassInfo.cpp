// Copyright Electronic CAD Monkey [ECM]

#include "ECMCharacterClassInfo.h"

TObjectPtr<UECMEnemySpecInfo>  UECMCharacterClassInfo::GetClassDefaultInfo(const FGameplayTag EnemyTag) const
{
	if( EnemyTag.IsValid() )
	{
		return CharacterClassInformation.FindRef(EnemyTag);
	}	
		return nullptr;
}
