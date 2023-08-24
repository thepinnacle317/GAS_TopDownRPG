// Copyright Pinnacle Gaming Studios


#include "AbilitySystem/Data/CharacterClassInfo.h"

FCharacterClassDefaultInfo UCharacterClassInfo::GetClassDefaultInfo(ECharacterClass CharacterClass)
{
	// Performs an assertion and checks for the information.
	return CharacterClassInformation.FindChecked(CharacterClass);
}
