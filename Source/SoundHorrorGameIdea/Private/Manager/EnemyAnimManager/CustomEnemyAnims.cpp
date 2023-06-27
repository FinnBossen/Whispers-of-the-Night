#include "Manager/EnemyAnimManager/CustomEnemyAnims.h"

UCustomEnemyAnims::UCustomEnemyAnims(const FObjectInitializer& ObjectInitializer)
{
}

void UCustomEnemyAnims::BeginPlay()
{
	Super::BeginPlay();
}

void UCustomEnemyAnims::SpawnAndAttachAccessories(USkeletalMeshComponent* SkeletalMeshComponent, AActor* Owner) const
{
	// Loop through all the accessories in the array
	for(const auto& Accessory : StoredCustomEnemyAccessory)
	{
		// Call the function in UCustomEnemyAccessory to spawn and attach the accessory
		Accessory->SpawnAccessoryAtSocket(SkeletalMeshComponent, Owner);
	}
}
