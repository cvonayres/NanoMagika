// Copyright Electronic CAD Monkey [ECM]


#include "ECMLevelUpInformation.h"

int32 UECMLevelUpInformation::FindLevelForXP(int32 XP) const
{
	int32 Level = 1;
	bool bSearching = true;
	while (bSearching)
	{
		// LevelUpInformation[1] = Level 1 Information
		// LevelUpInformation[2] = Level 1 Information
		if (LevelUpInformation.Num() - 1 <= Level) return Level;

		if (XP >= LevelUpInformation[Level].LevelUpThreshold)
		{
			++Level;
		}
		else
		{
			bSearching = false;
		}
	}
	return Level;
}