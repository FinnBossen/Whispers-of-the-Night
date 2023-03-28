// Fill out your copyright notice in the Description page of Project Settings.


#include "Manager/VisualClueManager/VisualCueManager.h"

// Sets default values
AVisualCueManager::AVisualCueManager()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AVisualCueManager::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AVisualCueManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

UVisualClue* AVisualCueManager::GetRandomVisualClueOfType(EVisualClueType ClueType)
{
	// Get all visual clues of a specific type
	TArray<UVisualClue*> VisualCluesOfType;
	for (UVisualClue* VisualClue : StoredVisualClues)
	{
		if (VisualClue->VisualClueType == ClueType)
		{
			VisualCluesOfType.Add(VisualClue);
		}
	}

	// Get random visual clue of a specific type
	if (VisualCluesOfType.Num() > 0)
	{
		return VisualCluesOfType[FMath::RandRange(0, VisualCluesOfType.Num() - 1)];
	}

	// return nullptr if no visual clues of a specific type are found
	return nullptr;
}
