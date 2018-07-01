// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "ArKDownGameMode.h"
#include "ArKDownHUD.h"
#include "Player/FirstPersonCharacter.h"
#include "UObject/ConstructorHelpers.h"

AArKDownGameMode::AArKDownGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/Character/GameCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AArKDownHUD::StaticClass();
}
