// Copyright Electronic CAD Monkey [ECM]

#include "ECMCharacterClassInfo.h"

TObjectPtr<UECMEnemySpecInfo>  UECMCharacterClassInfo::GetClassDefaultInfo(FGameplayTag EnemyTag)
{
	return CharacterClassInformation.FindChecked(EnemyTag);
}
