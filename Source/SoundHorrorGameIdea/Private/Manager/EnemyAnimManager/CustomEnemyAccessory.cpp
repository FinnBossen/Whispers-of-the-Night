// Fill out your copyright notice in the Description page of Project Settings.


#include "Manager/EnemyAnimManager/CustomEnemyAccessory.h"

// Sets default values for this component's properties
UCustomEnemyAccessory::UCustomEnemyAccessory()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void UCustomEnemyAccessory::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void UCustomEnemyAccessory::SpawnAccessoryAtSocket(AActor* Owner) const
{
	// Get a reference to the world

	if(UWorld* World = GetWorld(); World && AccessoryMesh && Owner && !AccessorySocketName.IsNone())
	{
		// Spawn the accessory mesh

		// If the mesh was successfully spawned
		if(const AActor* SpawnedAccessory = World->SpawnActor<AActor>(AccessoryMesh->GetClass()))
		{
			// Cast the spawned actor to a UStaticMeshComponent

			// If the cast was successful
			if(UStaticMeshComponent* AccessoryMeshComponent = Cast<UStaticMeshComponent>(SpawnedAccessory->GetRootComponent()))
			{
				// Set the static mesh
				AccessoryMeshComponent->SetStaticMesh(AccessoryMesh);

				// Attach the accessory to the specified socket on the owner's mesh
				AccessoryMeshComponent->AttachToComponent(Owner->GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform, AccessorySocketName);
			}
		}
	}
}

