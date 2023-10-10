// Copyright Electronic CAD Monkey [ECM]

#include "ECMCharacterClassInfo.h"

FCharacterClassDefaultInfo UECMCharacterClassInfo::GetClassDefaultInfo(ECharacterClass CharacterClass)
{
	return CharacterClassInformation.FindChecked(CharacterClass);
}
