// Copyright Epic Games, Inc. All Rights Reserved.

#include "gam_415_fps_humanGameMode.h"
#include "gam_415_fps_humanCharacter.h"
#include "UObject/ConstructorHelpers.h"

Agam_415_fps_humanGameMode::Agam_415_fps_humanGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
