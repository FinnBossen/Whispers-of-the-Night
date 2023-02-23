// Fill out your copyright notice in the Description page of Project Settings.


#include "SoundHorrorGameIdea/Public/Manager/JumpScareManager/JumpScareManager.h"

// Sets default values
AJumpScareManager::AJumpScareManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AJumpScareManager::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AJumpScareManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

UCustomJumpScare* AJumpScareManager::GetRandomJumpScare()
{
	const int RandomIndex = FMath::RandRange(0, StoredJumpScares.Num() - 1);
	return StoredJumpScares[RandomIndex];
}

