// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TargetPoint.h"
#include "GameFramework/Actor.h"
#include "WayPoint.generated.h"

UCLASS()
class SOUNDHORRORGAMEIDEA_API AWayPoint final : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AWayPoint();
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components")
	ATargetPoint* TargetPoint;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	FVector WayPointLocation;
	bool Used = false;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void OnConstruction(const FTransform &Transform) override;

	FVector3d GetWayPointLocation() const;

	bool IsUsed() const;

	void SetIsUsed(bool IsUsed);

	ATargetPoint* GetTargetPoint() const;
};
