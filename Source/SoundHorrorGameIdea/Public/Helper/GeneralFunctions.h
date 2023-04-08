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
	TArray<AGhostEnemy*> GetAllEnemiesThePlayerIsHearing() const;
	
	template <typename T>
	UFUNCTION(BlueprintCallable, Category = Array)
	static void  RemoveDuplicatesInArray(TArray<T>& InArray);
};
