// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WayPoint.h"
#include "GameFramework/Actor.h"
#include "WayPointManager.generated.h"

UCLASS()
class SOUNDHORRORGAMEIDEA_API AWayPointManager final : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWayPointManager();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = StoredJumpScares)
	TArray<AWayPoint*> StoredWayPoints;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	AWayPoint* GetNearestWayPointToLocation(const FVector& Location);

	TArray<AWayPoint*> SortStoredWayPointsByDistance( FVector Location);

	TArray<AWayPoint*> GetWayPointsFromWorld() const;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = EnemyWayPoints)
	TArray<AWayPoint*> GetWayPointsForEnemy(const AActor* Enemy, int32 NumberOfWayPoints);

};
