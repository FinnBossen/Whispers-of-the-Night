// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Manager/ESoundClueType.h"
#include "Manager/EVisualClueType.h"
#include "Manager/SoundClueManager/SoundClue.h"
#include "Manager/VisualClueManager/VisualClue.h"
#include "GhostEnemy.generated.h"

UCLASS()
class SOUNDHORRORGAMEIDEA_API AGhostEnemy : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AGhostEnemy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;



public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, Category = SoundCluesStoredAtEnemy)
	TMap<ESoundClueType, USoundClue*> SoundClues;

	UPROPERTY(EditAnywhere, Category = VisualCluesStoredAtEnemy)
	TMap<EVisualClueType, UVisualClue*> VisualClues;

};
