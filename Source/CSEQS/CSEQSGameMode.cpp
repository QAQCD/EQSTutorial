// Copyright Epic Games, Inc. All Rights Reserved.

#include "CSEQSGameMode.h"
#include "CSEQSCharacter.h"
#include "UObject/ConstructorHelpers.h"

ACSEQSGameMode::ACSEQSGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
