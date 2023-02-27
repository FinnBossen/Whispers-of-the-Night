// Fill out your copyright notice in the Description page of Project Settings.


#include "Manager/WayPointManager/WayPointManager.h"

#include "EngineUtils.h"

// Sets default values
AWayPointManager::AWayPointManager()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Find all WayPoint actors in the world and add them to the WayPoints array
	StoredWayPoints = GetWayPointsFromWorld();
	
}

// Called when the game starts or when spawned
void AWayPointManager::BeginPlay()
{
	Super::BeginPlay();
	
}


float Distance(const FVector Point1, const FVector Point2)
{
	return FVector::Dist(Point1, Point2);
}

bool CompareVectorsForNearest(const FVector& Vector1, const FVector& Vector2, const FVector& Location)
{
	return Distance(Vector1, Location) < Distance(Vector2, Location);
}

bool CompareWayPoints(const AWayPoint& WayPoint1, const AWayPoint& WayPoint2, const FVector& Location)
{
	return FVector::Dist(WayPoint1.GetWayPointLocation(), Location) < FVector::Dist(
		WayPoint2.GetWayPointLocation(), Location);
}

AWayPoint* AWayPointManager::GetNearestWayPointToLocation(const FVector& Location)
{
	TArray<AWayPoint*> SortedWayPoints = SortStoredWayPointsByDistance(Location);

	// Return the first waypoint in the sorted array
	return SortedWayPoints[0];
}

TArray<AWayPoint*> AWayPointManager::SortStoredWayPointsByDistance(FVector Location)
{
	TArray<AWayPoint*> SortedWayPoints;

	// Copy the waypoints from the input array to the new array
	SortedWayPoints.Append(StoredWayPoints);

	// Sort the array of waypoints by distance from the location
	StoredWayPoints.Sort([&Location](const AWayPoint& WayPoint1, const AWayPoint& WayPoint2)
	{
		return CompareWayPoints(WayPoint1, WayPoint2, Location);
	});

	return SortedWayPoints;
}

TArray<AWayPoint*> AWayPointManager::GetWayPointsFromWorld() const
{
	TArray<AWayPoint*> WayPoints;

	// Find all WayPoint actors in the world and add them to the WayPoints array
	if (const UWorld* World = GetWorld())
	{
		for (TActorIterator<AWayPoint> IteratedWayPoint(World); IteratedWayPoint; ++IteratedWayPoint)
		{
			if (AWayPoint* WayPoint = *IteratedWayPoint)
			{
				WayPoints.Add(WayPoint);
			}
		}
	}

	return WayPoints;
}


// Called every frame
void AWayPointManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

TArray<AWayPoint*> AWayPointManager::GetWayPointsForEnemy(const AActor* Enemy, const int32 NumberOfWayPoints)
{
	TArray<AWayPoint*> SortedWayPoints = SortStoredWayPointsByDistance(Enemy->GetActorLocation());

	TArray<AWayPoint*> WayPointsToReturn;

	for (int32 i = 0; i < SortedWayPoints.Num(); i++)
	{
		// If the waypoint is not used, add it to the array of waypoints to return
		if (!SortedWayPoints[i]->IsUsed())
		{
			WayPointsToReturn.Add(SortedWayPoints[i]);
		}
		// If the number of waypoints to return is equal to the number of waypoints to return, break the loop
		if (WayPointsToReturn.Num() == NumberOfWayPoints)
		{
			break;
		}
	}
	return WayPointsToReturn;
}

void AWayPointManager::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
}
