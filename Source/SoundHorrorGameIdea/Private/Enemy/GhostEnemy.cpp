// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy//GhostEnemy.h"

// Sets default values
AGhostEnemy::AGhostEnemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AGhostEnemy::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGhostEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AGhostEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

TMap<ESoundClueType, USoundClue*> AGhostEnemy::GetSoundClues() const
{
	return SoundClues;
}

