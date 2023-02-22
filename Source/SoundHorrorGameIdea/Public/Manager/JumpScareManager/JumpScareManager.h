// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CustomJumpScare.h"
#include "GameFramework/Actor.h"
#include "JumpScareManager.generated.h"

UCLASS()
class SOUNDHORRORGAMEIDEA_API AJumpScareManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AJumpScareManager();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = StoredJumpScares)
	TArray<TAssetSubclassOf<UCustomJumpScare>> StoredJumpScares;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
};
