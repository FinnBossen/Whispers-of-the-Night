// Fill out your copyright notice in the Description page of Project Settings.


#include "Manager/WayPointManager/WayPoint.h"

#include "Blueprint/UserWidget.h"

// Sets default values
AWayPoint::AWayPoint()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	WayPointLocation = GetActorLocation();

	if(TargetPoint != nullptr)
	{
		return;
	}

	/**
	// Create a new TargetPoint component
	ATargetPoint* NewTargetPoint = CreateDefaultSubobject<ATargetPoint>(TEXT("TargetPoint"));

	// Attach the TargetPoint to the root component
	if (NewTargetPoint != nullptr && GetRootComponent() != nullptr)
	{
		NewTargetPoint->AttachToComponent(GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
	}

	TargetPoint = NewTargetPoint;
	**/
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

void AWayPoint::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	if(TargetPoint != nullptr)
	{
		return;
	}

	// Create a new TargetPoint component
	ATargetPoint* NewTargetPoint = NewObject<ATargetPoint>(this);

	// Attach the TargetPoint to the root component
	if (NewTargetPoint != nullptr && GetRootComponent() != nullptr)
	{
		NewTargetPoint->AttachToComponent(GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
	}

	TargetPoint = NewTargetPoint;
}

