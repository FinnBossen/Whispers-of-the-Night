// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TargetPoint.h"
#include "GameFramework/Actor.h"
#include "Manager/EAIActionType.h"
#include "Manager/FActionInfo.h"
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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	bool IsWaiting;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	EAIActionType WayPointType;

	UPROPERTY(BlueprintReadOnly, Category = "Components")
	FVector WayPointLocation;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	bool Used = false;



public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void OnConstruction(const FTransform &Transform) override;
	
	FVector3d GetWayPointLocation() const;

	UFUNCTION(BlueprintCallable, Category = "Action")
	FActionInfo GetActionInfo() const;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Action")
	void WayPointAction();

	bool IsUsed() const;

	void SetIsUsed(bool IsUsed);

	ATargetPoint* GetTargetPoint() const;
};
