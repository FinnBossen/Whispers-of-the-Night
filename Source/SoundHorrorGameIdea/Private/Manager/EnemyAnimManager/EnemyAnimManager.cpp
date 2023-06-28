#include "Manager/EnemyAnimManager/EnemyAnimManager.h"

AEnemyAnimManager::AEnemyAnimManager()
{
}

void AEnemyAnimManager::BeginPlay()
{
	Super::BeginPlay();
}

void AEnemyAnimManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

UCustomEnemyAnims* AEnemyAnimManager::GetRandomCustomEnemyAnims()
{
	// Return a random custom enemy anims
	const int Index = FMath::RandRange(0, StoredCustomEnemyAnims.Num() - 1);
	return StoredCustomEnemyAnims[Index];
}

UCustomEnemyAnims* AEnemyAnimManager::GetPlayerCustomAnims() const
{
	return StoredCustomPlayerAnims;
}
