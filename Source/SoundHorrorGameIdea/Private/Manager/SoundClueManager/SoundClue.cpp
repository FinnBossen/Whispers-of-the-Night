// Fill out your copyright notice in the Description page of Project Settings.


#include "Manager/SoundClueManager/SoundClue.h"

#include "Components/AudioComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Manager/SoundClueManager/SoundCluesManager.h"

USoundClue::USoundClue(const FObjectInitializer& ObjectInitializer): Super(ObjectInitializer)
{
}

//BeginPlay Function
void USoundClue::BeginPlay()
{
	Super::BeginPlay();
	// Get Owner class and cast to SoundCluesManager
	const ASoundCluesManager* SoundCluesManager = Cast<ASoundCluesManager>(GetOwner());
	// Check if SoundCluesManager is valid
	if (SoundCluesManager == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("SoundClue: SoundCluesManager is nullptr"));
		return;
	}

	SoundAttenuationSettings = SoundCluesManager->SoundAttenuationSettings;


	// Get a reference to the player character or listener
	PlayerActor = GetWorld()->GetFirstPlayerController()->GetPawn();
}

// Play the sound that is attached to the sound clue

void USoundClue::PlaySound(AActor* Owner)
{
	if (AudioComponent != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("SoundClue: %s"), *Owner->GetName());
		AudioComponent->Play();
		return;
	}
	USceneComponent* OwnerRootComponent = Owner->GetRootComponent();
	// Spawn Sound Attached to the owner
	AudioComponent = UGameplayStatics::SpawnSoundAttached(Sound, OwnerRootComponent, NAME_None, FVector::ZeroVector,
	                                                      EAttachLocation::KeepRelativeOffset, true, 1.0f, 1.0f, 0.0f,
	                                                      SoundAttenuationSettings);
	// Print owner name to screen
	UE_LOG(LogTemp, Warning, TEXT("SoundClue: %s"), *Owner->GetName());
	AudioComponent->AttachToComponent(OwnerRootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	AudioComponent->RegisterComponent();
}

void USoundClue::StopSound() const
{
	if (AudioComponent == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("No AudioComponent is set for SoundClue: %s"), *GetName());
		return;
	}
	if (AudioComponent->IsPlaying())
	{
		AudioComponent->Stop();
	}
}

bool USoundClue::IsHeardByPlayer() const
{
	if (AudioComponent == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("No AudioComponent is set for SoundClue: %s"), *GetName());
		return false;
	}

	if (!AudioComponent->IsPlaying())
	{
		return false;
	}
	
	if (PlayerActor == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("No PlayerActor is set for SoundClue: %s"), *GetName());
		return false;
	}

	const FVector AudioComponentLocation = AudioComponent->GetComponentLocation();

	const FVector GetPlayerLocation = PlayerActor->GetActorLocation();

	const float DistanceBetweenAudioAndPlayer = AudioComponentLocation.Distance(AudioComponentLocation, GetPlayerLocation);

	if (SoundAttenuationSettings == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("No AttenuationSettings set for SoundClue: %s"), *GetName());
	}
	// Get the maximum audible distance of the audioComponent
	const float MaxAudibleDistance = SoundAttenuationSettings->Attenuation.GetMaxDimension();

	if (DistanceBetweenAudioAndPlayer >= MaxAudibleDistance)
	{
		return false;
	}

	return true;
}
