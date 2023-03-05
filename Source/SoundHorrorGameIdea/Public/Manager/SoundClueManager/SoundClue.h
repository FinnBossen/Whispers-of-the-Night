
// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Manager/ESoundClueType.h"
#include "SoundClue.generated.h"

UCLASS()
class SOUNDHORRORGAMEIDEA_API USoundClue final : public UActorComponent
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	explicit USoundClue(const FObjectInitializer& ObjectInitializer);
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SoundType)
	ESoundClueType SoundClueType;

	// A sound that can be player
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Sound)
	USoundBase* Sound;

	//Play the sound
	UFUNCTION(BlueprintCallable, Category = Sound)
	void PlaySound(FVector Location) const;

};
