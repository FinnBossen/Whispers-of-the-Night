// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "VisualClue.h"
#include "GameFramework/Actor.h"
#include "VisualCueManager.generated.h"

UCLASS()
class SOUNDHORRORGAMEIDEA_API AVisualCueManager final : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AVisualCueManager();

	UPROPERTY(EditAnywhere, Instanced, BlueprintReadWrite)
	TArray<UVisualClue*> StoredVisualClues;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
