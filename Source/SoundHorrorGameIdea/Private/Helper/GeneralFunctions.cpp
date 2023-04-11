// Fill out your copyright notice in the Description page of Project Settings.


#include "Helper/GeneralFunctions.h"
#include "Enemy/GhostEnemy.h"
#include "Engine/SCS_Node.h"
#include "Kismet/GameplayStatics.h"
#include "Manager/SoundClueManager/SoundCluesManager.h"

TArray<AGhostEnemy*> UGeneralFunctions::GetAllEnemiesThePlayerIsHearing(const AActor* ActorCallingFunction)
{
	// Get All SoundClues in World
	TArray<AActor*> EnemyActors;
	UGameplayStatics::GetAllActorsOfClass(ActorCallingFunction->GetWorld(), AGhostEnemy::StaticClass(), EnemyActors);

	// Check All SoundClues if they are heard by the player
	TArray<AGhostEnemy*> HeardGhostEnemies;
	for (AActor* EnemyActor : EnemyActors)
	{

		AGhostEnemy* GhostEnemy = Cast<AGhostEnemy>(EnemyActor);
		const AActor* ClassDefault = GhostEnemy->GetClass()->GetDefaultObject<AActor>();
		TArray<UActorComponent*> SoundClues;
		const USoundClue* StaticMeshComponent = GhostEnemy->FindComponentByClass<USoundClue>();

		UE_LOG(LogTemp, Display, TEXT("Could not cast actor to USoundClue Actor: %s"), *StaticMeshComponent->GetName());
		
		for (const UActorComponent* SoundClue : SoundClues)
		{
			//Cast SoundClue to USoundClue
			const USoundClue* SoundClueCast = Cast<USoundClue>(SoundClue);
			if (SoundClueCast == nullptr)
			{
				UE_LOG(LogTemp, Display, TEXT("Could not cast actor to USoundClue Actor: %s"), *EnemyActor->GetName());
				continue;
			}
			// Check if SoundClue is heard by the player
			if (!SoundClueCast->IsHeardByPlayer())
			{
				continue;
			}

			// Add GhostEnemy to Array
		
			if (GhostEnemy == nullptr)
			{
				UE_LOG(LogTemp, Display, TEXT("Could not cast actor to AGhostEnemy Actor: %s"), *EnemyActor->GetName());
				continue;
			}
			HeardGhostEnemies.Add(GhostEnemy);
		}
	}

	// Filter Array for duplicates
	RemoveDuplicatesInArray(HeardGhostEnemies);
	return HeardGhostEnemies;
}

bool UGeneralFunctions::GetClassBlueprintComponents(const TSubclassOf<UObject> ObjectClass, TArray<UActorComponent*>& OutComponents)
{
	if (!ensureAlwaysMsgf(ObjectClass, TEXT("Cannot get blueprint components of a null class.")))
	{
		return false;
	}

	if (UBlueprintGeneratedClass* BlueprintClass = Cast<UBlueprintGeneratedClass>(ObjectClass))
	{
		// Retrieve the hierarchy of blueprint classes for this CDO.
		TArray<const UBlueprintGeneratedClass*> BlueprintClasses;
		UBlueprintGeneratedClass::GetGeneratedClassesHierarchy(BlueprintClass, BlueprintClasses);
		for (const UBlueprintGeneratedClass* Class : BlueprintClasses)
		{
			if (Class->SimpleConstructionScript)
			{
				// And now we get the component from the nodes.
				TArray<USCS_Node*> CDONodes = Class->SimpleConstructionScript->GetAllNodes();
				for (USCS_Node* Node : CDONodes)
				{
					UActorComponent* CDOComponent = Node->GetActualComponentTemplate(BlueprintClass);
					OutComponents.Add(CDOComponent);
				}
			}
		}

		return true;
	}

	return false;
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

