// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Manager/ESoundClueType.h"
#include "Manager/EVisualClueType.h"
#include "Manager/EnemyAnimManager/CustomEnemyAnims.h"
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
	
	UFUNCTION( Category = Sound)
	TMap<ESoundClueType, USoundClue*> GetSoundClues() const;

	UFUNCTION(BlueprintCallable, Category = Sound)
	float GetNearestSoundCluePercentage() const;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = EnemyAnimationClass)
	UCustomEnemyAnims* CustomEnemyAnims;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SoundCluesStoredAtEnemy)
	TMap<ESoundClueType, USoundClue*> SoundClues;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = VisualCluesStoredAtEnemy)
	TMap<EVisualClueType, UVisualClue*> VisualClues;
};
