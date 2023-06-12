#pragma once

#include "CustomEnemyAnims.h"
#include "EnemyAnimManager.generated.h"


UCLASS()
class SOUNDHORRORGAMEIDEA_API AEnemyAnimManager final : public AActor
{
	GENERATED_BODY()
public:
	AEnemyAnimManager();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = StoredJumpScares)
	TArray<UCustomEnemyAnims*> StoredCustomEnemyAnims;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = StoredCustomEnemyAnims)
	UCustomEnemyAnims* GetRandomCustomEnemyAnims();
	
};
