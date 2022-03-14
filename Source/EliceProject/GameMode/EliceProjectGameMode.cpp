// Copyright Epic Games, Inc. All Rights Reserved.

#include "EliceProjectGameMode.h"
#include "../Character/PC/EliceProjectCharacter.h"
#include "UObject/ConstructorHelpers.h"

AEliceProjectGameMode::AEliceProjectGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
