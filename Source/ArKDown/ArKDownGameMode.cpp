// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "ArKDownGameMode.h"
#include "ArKDownHUD.h"
#include "ArKDownCharacter.h"
#include "UObject/ConstructorHelpers.h"

AArKDownGameMode::AArKDownGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AArKDownHUD::StaticClass();
}
