// Fill out your copyright notice in the Description page of Project Settings.


#include "Helper/GeneralFunctions.h"
#include "Enemy/GhostEnemy.h"
#include "Kismet/GameplayStatics.h"
#include "Manager/SoundClueManager/SoundCluesManager.h"

TArray<AGhostEnemy*> UGeneralFunctions::GetAllEnemiesThePlayerIsHearing() const
{
	// Get All SoundClues in World
	TArray<AActor*> SoundCluesActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASoundCluesManager::StaticClass(), SoundCluesActors);

	// Check All SoundClues if they are heard by the player
	TArray<AGhostEnemy*> HeardGhostEnemies;
	for (AActor* SoundCluesActor : SoundCluesActors)
	{
		// Cast SoundClue to SoundCluesManager
		const USoundClue* SoundClue = Cast<USoundClue>(SoundCluesActor);
		// Check if SoundClue is valid
		if (SoundClue == nullptr)
		{
			UE_LOG(LogTemp, Error, TEXT("SoundClue is nullptr"));
			continue;
		}

		// Check if SoundClue is SoundClue Parent is attached to a GhostEnemy
		AGhostEnemy* GhostEnemy = Cast<AGhostEnemy>(SoundClue->GetOwner());
		// Check if GhostEnemy is valid
		if (GhostEnemy == nullptr)
		{
			// SoundClue is not attached to GhostEnemy and can be ignored
			UE_LOG(LogTemp, Display, TEXT("Could not find GhostEnemy as Owmer of SoundClue Owner is: %s"), *SoundClue->GetOwner()->GetName());
			continue;
		}

		// Check if SoundClue is heard by the player
		if (SoundClue->IsHeardByPlayer())
		{
			// Add GhostEnemy to Array
			HeardGhostEnemies.Add(GhostEnemy);
		}
	}

	// Filter Array for duplicates
	RemoveDuplicatesInArray(HeardGhostEnemies);
	return HeardGhostEnemies;
}

template <typename T>
void UGeneralFunctions::RemoveDuplicatesInArray(TArray<T>& InArray)
{
	// Sort the array
	InArray.Sort();

	// Remove duplicates
	int32 NumDuplicates = 0;
	for (int32 i = 0; i < InArray.Num() - 1; i++)
	{
		if (InArray[i] == InArray[i + 1])
		{
			NumDuplicates++;
		}
	}

	if (NumDuplicates > 0)
	{
		InArray.RemoveAt(InArray.Num() - NumDuplicates, NumDuplicates);
	}
}

