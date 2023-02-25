// Copyright Epic Games, Inc. All Rights Reserved.

#include "GameMode/SoundHorrorGameIdeaGameMode.h"

#include "SoundHorrorGameIdea/Public/Character/SoundHorrorGameIdeaCharacter.h"
#include "SoundHorrorGameIdea/Public/Controller/SoundHorrorGameIdeaPlayerController.h"
#include "UObject/ConstructorHelpers.h"

ASoundHorrorGameIdeaGameMode::ASoundHorrorGameIdeaGameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = ASoundHorrorGameIdeaPlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TopDown/Blueprints/BP_TopDownCharacter"));
	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	// set default controller to our Blueprinted controller
	static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerBPClass(TEXT("/Game/TopDown/Blueprints/BP_TopDownPlayerController"));
	if(PlayerControllerBPClass.Class != NULL)
	{
		PlayerControllerClass = PlayerControllerBPClass.Class;
	}
}