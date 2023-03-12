// Fill out your copyright notice in the Description page of Project Settings.


#include "Manager/SoundClueManager/SoundClue.h"

#include "Components/AudioComponent.h"
#include "Kismet/GameplayStatics.h"

USoundClue::USoundClue(const FObjectInitializer& ObjectInitializer): Super(ObjectInitializer)
{
}

// Play the sound that is attached to the sound clue
void USoundClue::PlaySound()
{
	if (AudioComponent != nullptr)
	{
		AudioComponent->Play();
		return;
	}
	AudioComponent = UGameplayStatics::SpawnSoundAtLocation(this, Sound, GetOwner()->GetActorLocation());
	AudioComponent->AttachToComponent(GetOwner()->GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
	AudioComponent->RegisterComponent();
}

void USoundClue::StopSound() const
{
	if (AudioComponent == nullptr)
	{
		return;
	}
	if (AudioComponent->IsPlaying())
	{
		AudioComponent->Stop();
	}
}
