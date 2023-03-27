
// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Manager/ESoundClueType.h"
#include "SoundClue.generated.h"

UCLASS(EditInlineNew)
class SOUNDHORRORGAMEIDEA_API USoundClue final : public UActorComponent
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	explicit USoundClue(const FObjectInitializer& ObjectInitializer);
	//Begin Play Function
	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SoundType)
	ESoundClueType SoundClueType;

	// A sound that can be played
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Sound)
	USoundBase* Sound;
	
	//Play the sound
	UFUNCTION(BlueprintCallable, Category = Sound)
	void PlaySound(AActor* Owner);

	//Play the sound
	UFUNCTION(BlueprintCallable, Category = Sound)
	void StopSound() const;
private:
	UPROPERTY(EditAnywhere, Category = Sound)
	UAudioComponent* AudioComponent;

	UPROPERTY(EditAnywhere, Category = Sound)
	USoundAttenuation* SoundAttenuationSettings;

};
