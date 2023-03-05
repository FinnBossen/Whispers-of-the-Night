// Fill out your copyright notice in the Description page of Project Settings.


#include "Manager/SoundClueManager/SoundClue.h"

#include "Kismet/GameplayStatics.h"

USoundClue::USoundClue(const FObjectInitializer& ObjectInitializer): Super(ObjectInitializer)
{
}

// Play the sound that is attached to the sound clue
void USoundClue::PlaySound(const FVector Location) const
{
	UGameplayStatics::PlaySoundAtLocation(this, Sound, Location);
}

