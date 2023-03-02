
// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Manager/ESoundClueType.h"
#include "SoundClue.generated.h"

UCLASS()
class SOUNDHORRORGAMEIDEA_API ASoundClue : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASoundClue();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SoundType)
	ESoundClueType SoundClueType;

	// A sound that can be player
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Sound)
	USoundBase* Sound;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//Play the sound
	UFUNCTION(BlueprintCallable, Category = Sound)
	void PlaySound() const;

};
