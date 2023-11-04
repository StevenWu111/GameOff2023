// Copyright Epic Games, Inc. All Rights Reserved.

#include "GameOffGameMode.h"
#include "GameOffCharacter.h"
#include "UObject/ConstructorHelpers.h"

AGameOffGameMode::AGameOffGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
