// Fill out your copyright notice in the Description page of Project Settings.


#include "Helper/GeneralFunctions.h"

#include "Components/CanvasPanel.h"
#include "Components/Widget.h"
#include "Enemy/GhostEnemy.h"
#include "Engine/SCS_Node.h"
#include "Kismet/GameplayStatics.h"
#include "Manager/SoundClueManager/SoundCluesManager.h"
#include "GameFramework/Actor.h"
#include "Components/CapsuleComponent.h"

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


		for (const auto& SoundCluePair : GhostEnemy->GetSoundClues())
		{
			//Cast SoundClue to USoundClue
			const USoundClue* SoundClueCast = Cast<USoundClue>(SoundCluePair.Value);
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

void UGeneralFunctions::MuteAllEnemiesInArrayExceptSelected(TArray<AGhostEnemy*> GhostEnemies,
                                                            AGhostEnemy* GhostSelected)
{
	// Remove GhostSelected from Array
	GhostEnemies.Remove(GhostSelected);
	// Mute all GhostEnemies in Array
	MuteAllEnemiesInArray(GhostEnemies);
}

void UGeneralFunctions::MuteAllEnemiesInArray(TArray<AGhostEnemy*> GhostEnemies)
{
	// Loop through all GhostEnemies
	for (const AGhostEnemy* GhostEnemy : GhostEnemies)
	{
		// Loop through all SoundClues of the GhostEnemy
		for (const auto& SoundCluePair : GhostEnemy->GetSoundClues())
		{
			// Cast SoundClue to USoundClue
			const USoundClue* SoundClueCast = Cast<USoundClue>(SoundCluePair.Value);
			if (SoundClueCast == nullptr)
			{
				UE_LOG(LogTemp, Display, TEXT("Could not cast actor to USoundClue Actor: %s"), *GhostEnemy->GetName());
				continue;
			}
			// Mute SoundClue
			SoundClueCast->MuteSound();
		}
	}
}

void UGeneralFunctions::UnMuteAllEnemiesInArray(TArray<AGhostEnemy*> GhostEnemies)
{
	// Loop through all GhostEnemies
	for (const AGhostEnemy* GhostEnemy : GhostEnemies)
	{
		// Loop through all SoundClues of the GhostEnemy
		for (const auto& SoundCluePair : GhostEnemy->GetSoundClues())
		{
			// Cast SoundClue to USoundClue
			const USoundClue* SoundClueCast = Cast<USoundClue>(SoundCluePair.Value);
			if (SoundClueCast == nullptr)
			{
				UE_LOG(LogTemp, Display, TEXT("Could not cast actor to USoundClue Actor: %s"), *GhostEnemy->GetName());
				continue;
			}
			// UnMute SoundClue
			SoundClueCast->UnMuteSound();
		}
	}
}

bool UGeneralFunctions::GetClassBlueprintComponents(const TSubclassOf<UObject> ObjectClass,
                                                    TArray<UActorComponent*>& OutComponents)
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


float UGeneralFunctions::GetAngleBetweenTwoVector2D(const FVector2D VectorA, const FVector2D VectorB)
{
	const float AngleRadians = FMath::Atan2(VectorB.Y - VectorA.Y, VectorB.X - VectorA.X);
	return FMath::RadiansToDegrees(AngleRadians);
}

void UGeneralFunctions::GetActorScreenLocation(AActor* Actor, FVector2D& ActorScreenLocation)
{
	// Get a reference to the player controller
	const APlayerController* PlayerController = Actor->GetWorld()->GetFirstPlayerController();

	// Get the world location of the actor you want to convert
	const FVector ActorWorldLocation = Actor->GetActorLocation();

	// Convert the world location to screen location
	UGameplayStatics::ProjectWorldToScreen(PlayerController, ActorWorldLocation, ActorScreenLocation);
}

bool UGeneralFunctions::IsPointInBox(const FVector2D Point, const FBox2D Box)
{
	return Box.IsInside(Point);
}

FBox2D UGeneralFunctions::GetWidgetBoxRelativeToCanvas(UWidget* Widget, UCanvasPanel* Canvas)
{
	if (Widget == nullptr || Canvas == nullptr)
	{
		return FBox2D();
	}

	const FGeometry WidgetGeometry = Widget->GetCachedGeometry();
	const FGeometry CanvasGeometry = Canvas->GetCachedGeometry();

	const FVector2D WidgetAbsolutePosition = WidgetGeometry.GetAbsolutePosition();
	const FVector2D WidgetSize = WidgetGeometry.GetLocalSize();

	const FVector2D PositionRelativeToCanvas = CanvasGeometry.AbsoluteToLocal(WidgetAbsolutePosition);

	// The returned box will have its Min point at the top-left of the widget,
	// and its Max point at the bottom-right.
	return FBox2D(PositionRelativeToCanvas, PositionRelativeToCanvas + WidgetSize);
}

float UGeneralFunctions::GetFloatDifference(const float FloatA, const float FloatB)
{
	const float Difference = FMath::Abs(FloatA - FloatB);
	return Difference;
}

void UGeneralFunctions::RotateCapsule(UCapsuleComponent* Capsule, const float Degree)
{
	if(Capsule)
	{
		FRotator CurrentRotation = Capsule->GetComponentRotation();

		// Add the rotation degree to the yaw component of the rotation
		CurrentRotation.Yaw += Degree;

		// Set the new rotation for the capsule
		Capsule->SetWorldRotation(CurrentRotation);
	}
}

bool UGeneralFunctions::IsPointInWidget(UCanvasPanel* Canvas,const FVector2D Point, UWidget* Widget)
{
	// Check for a null widget.
	if (!Widget) return false;

	// Get the widget's bounding box.
	const FBox2D Box = GetWidgetBoxRelativeToCanvas(Widget, Canvas);

	// Check if the point is inside the box.
	return IsPointInBox(Point, Box);
}

float UGeneralFunctions::GetMaxFloat()
{
	return MAX_FLT;
}
