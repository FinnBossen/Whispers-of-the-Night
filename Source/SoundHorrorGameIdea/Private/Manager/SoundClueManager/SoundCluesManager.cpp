// Fill out your copyright notice in the Description page of Project Settings.


#include "Manager/SoundClueManager/SoundCluesManager.h"

// Sets default values
ASoundCluesManager::ASoundCluesManager()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ASoundCluesManager::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ASoundCluesManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

USoundClue* ASoundCluesManager::GetRandomSoundClueOfType(const ESoundClueType ClueType)
{
	/*
	// Get all sound clues of a specific type
	TArray<ASoundClue> SoundCluesOfType;
	for (ASoundClue SoundClue : StoredSoundClues)
	{
		if (SoundClue->SoundClueType == ClueType)
		{
			SoundCluesOfType.Add(SoundClue);
		}
	}

	// Get random sound clue of a specific type
	if (SoundCluesOfType.Num() > 0)
	{
		const int32 RandomIndex = FMath::RandRange(0, SoundCluesOfType.Num() - 1);
		return SoundCluesOfType[RandomIndex];
	}

	// return nullptr if no sound clues of a specific type are found
	return nullptr;
	*/
	return nullptr;
}
