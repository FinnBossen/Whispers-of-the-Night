// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CustomEnemyAccessory.h"
#include "Engine/DataAsset.h"
#include "CustomEnemyAccessoryAsset.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class SOUNDHORRORGAMEIDEA_API UCustomEnemyAccessoryAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Accessory)
	UCustomEnemyAccessory* CustomAccessory;
};
