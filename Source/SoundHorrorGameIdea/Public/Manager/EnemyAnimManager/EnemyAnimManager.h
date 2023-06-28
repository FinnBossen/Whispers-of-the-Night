#pragma once

#include "CustomEnemyAnims.h"
#include "EnemyAnimManager.generated.h"


UCLASS()
class SOUNDHORRORGAMEIDEA_API AEnemyAnimManager final : public AActor
{
	GENERATED_BODY()
public:
	AEnemyAnimManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = StoredAnims)
	UCustomEnemyAnims* StoredCustomPlayerAnims;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = StoredAnims)
	TArray<UCustomEnemyAnims*> StoredCustomEnemyAnims;
	
	UFUNCTION(BlueprintCallable, Category = StoredCustomEnemyAnims)
	UCustomEnemyAnims* GetRandomCustomEnemyAnims();

	UFUNCTION(BlueprintCallable, Category = StoredCustomEnemyAnims)
	UCustomEnemyAnims* GetPlayerCustomAnims() const;
	
};
