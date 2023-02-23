// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CustomJumpScare.generated.h"

/**
 * 
 */
UCLASS()
class SOUNDHORRORGAMEIDEA_API UCustomJumpScare : public UUserWidget
{
	GENERATED_BODY()

public:
	explicit UCustomJumpScare(const FObjectInitializer& ObjectInitializer);
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Audio)
	USoundBase* JumpScareSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Texture)
	UTexture2D* JumpScareTexture;
};
