// Fill out your copyright notice in the Description page of Project Settings.


#include "Manager/EnemyAnimManager/CustomEnemyAccessory.h"

class AStaticMeshActor;
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

void UCustomEnemyAccessory::SpawnAccessoryAtSocket(USkeletalMeshComponent* SkeletalMeshComponent, AActor* Owner) const
{
	// Get a reference to the world
	// Check if the SkeletalMeshComponent and AccessoryMesh are valid
	if (SkeletalMeshComponent && AccessoryMesh)
	{
		// Create the StaticMeshComponent
		UStaticMeshComponent* StaticMeshComponent = NewObject<UStaticMeshComponent>(Owner, UStaticMeshComponent::StaticClass());

		// Set the Static Mesh
		StaticMeshComponent->SetStaticMesh(AccessoryMesh);

		// Register the component to the game
		StaticMeshComponent->RegisterComponent();
        
		// Attach the Static Mesh to the SkeletalMeshComponent on the specified socket
		StaticMeshComponent->AttachToComponent(SkeletalMeshComponent, FAttachmentTransformRules::SnapToTargetIncludingScale, AccessorySocketName);
	}
}

void UCustomEnemyAccessory::SpawnAccessoryAtSocketWithoutShadow(USkeletalMeshComponent* SkeletalMeshComponent,
	AActor* Owner) const
{
	SkeletalMeshComponent->SetCastShadow(false);
	// Get a reference to the world
	// Check if the SkeletalMeshComponent and AccessoryMesh are valid
	if (SkeletalMeshComponent && AccessoryMesh)
	{
		// Create the StaticMeshComponent
		UStaticMeshComponent* StaticMeshComponent = NewObject<UStaticMeshComponent>(Owner, UStaticMeshComponent::StaticClass());

		StaticMeshComponent->SetCastShadow(false);
		// Set the Static Mesh
		StaticMeshComponent->SetStaticMesh(AccessoryMesh);

		// Register the component to the game
		StaticMeshComponent->RegisterComponent();
        
		// Attach the Static Mesh to the SkeletalMeshComponent on the specified socket
		StaticMeshComponent->AttachToComponent(SkeletalMeshComponent, FAttachmentTransformRules::SnapToTargetIncludingScale, AccessorySocketName);
	}
}

