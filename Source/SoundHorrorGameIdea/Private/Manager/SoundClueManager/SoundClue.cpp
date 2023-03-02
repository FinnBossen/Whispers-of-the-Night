// Fill out your copyright notice in the Description page of Project Settings.


#include "Manager/SoundClueManager/SoundClue.h"

#include "Kismet/GameplayStatics.h"

// Sets default values
ASoundClue::ASoundClue()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASoundClue::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASoundClue::Tick(const float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Play the sound that is attached to the sound clue
void ASoundClue::PlaySound() const
{
	UGameplayStatics::PlaySoundAtLocation(this, Sound, GetActorLocation());
}

