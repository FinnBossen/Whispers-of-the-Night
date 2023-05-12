// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enemy/GhostEnemy.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "GeneralFunctions.generated.h"

/**
 * 
 */
UCLASS()
class SOUNDHORRORGAMEIDEA_API UGeneralFunctions : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = Sound)
	static TArray<AGhostEnemy*> GetAllEnemiesThePlayerIsHearing(const AActor* ActorCallingFunction);


	UFUNCTION(BlueprintCallable, Category = Sound)
	static void MuteAllEnemiesInArrayExceptSelected(TArray<AGhostEnemy*> GhostEnemies, AGhostEnemy* GhostSelected);

	UFUNCTION(BlueprintCallable, Category = Sound)
	static void MuteAllEnemiesInArray(TArray<AGhostEnemy*> GhostEnemies);

	UFUNCTION(BlueprintCallable, Category = Sound)
	static void UnMuteAllEnemiesInArray(TArray<AGhostEnemy*> GhostEnemies);

	template <typename T>
	UFUNCTION(BlueprintCallable, Category = Array)
	static void RemoveDuplicatesInArray(TArray<T>& InArray);

	UFUNCTION(BlueprintCallable, Category = Array)
	static bool GetClassBlueprintComponents(TSubclassOf<UObject> ObjectClass, TArray<UActorComponent*>& OutComponents);

	UFUNCTION(BlueprintCallable, Category = Vector2D)
	static float GetAngleBetweenTwoVector2D(FVector2D VectorA, FVector2D VectorB);

	UFUNCTION(BlueprintCallable, Category = "Actor")
	static void GetActorScreenLocation(AActor* Actor, FVector2D& ActorScreenLocation);

	UFUNCTION(BlueprintCallable, Category = "Math|Float")
	static float GetFloatDifference(float FloatA, float FloatB);

	UFUNCTION(BlueprintCallable, Category = "Math|Float")
	static float GetMaxFloat();
};
