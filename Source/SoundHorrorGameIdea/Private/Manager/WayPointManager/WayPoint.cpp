// Fill out your copyright notice in the Description page of Project Settings.


#include "Manager/WayPointManager/WayPoint.h"

#include "Blueprint/UserWidget.h"

// Sets default values
AWayPoint::AWayPoint()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	WayPointLocation = GetActorLocation();

	if (UWorld* World = GetWorld())
	{
		if (UStaticMeshComponent* RootComp = Cast<UStaticMeshComponent>(GetRootComponent()))
		{
			const FVector Location = GetActorLocation() + FVector(0.f, 0.f, 100.f); // Offset the target point above the way point
			const FRotator Rotation = FRotator::ZeroRotator;
			if (ATargetPoint* TargetP = World->SpawnActor<ATargetPoint>(Location, Rotation))
			{
				TargetP->AttachToComponent(RootComp, FAttachmentTransformRules::KeepWorldTransform);
			}
		}
	}
}

FVector3d AWayPoint::GetWayPointLocation() const
{
	return WayPointLocation;
}

bool AWayPoint::IsUsed() const
{
	return Used;
}

void AWayPoint::SetIsUsed(bool IsUsed)
{
	this->Used = IsUsed;
}

ATargetPoint* AWayPoint::GetTargetPoint() const
{
	return TargetPoint;
}

// Called when the game starts or when spawned
void AWayPoint::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AWayPoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
