// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SoundClue.h"
#include "GameFramework/Actor.h"
#include "Manager/ESoundClueType.h"
#include "SoundCluesManager.generated.h"

UCLASS()
class SOUNDHORRORGAMEIDEA_API ASoundCluesManager final : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASoundCluesManager();
	UPROPERTY(EditAnywhere, Instanced, BlueprintReadWrite)
	TArray<USoundClue*> StoredSoundClues;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USoundAttenuation* SoundAttenuationSettings;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = StoredJumpScares)
	USoundClue* GetRandomSoundClueOfType(ESoundClueType ClueType);

};
