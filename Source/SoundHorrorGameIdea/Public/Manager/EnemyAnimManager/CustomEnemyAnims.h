#pragma once
#include "CustomEnemyAnims.generated.h"


UCLASS(EditInlineNew, blueprintable)
class SOUNDHORRORGAMEIDEA_API UCustomEnemyAnims final : public UActorComponent
{
	GENERATED_BODY()
public:	
	// Sets default values for this actor's properties
	explicit UCustomEnemyAnims(const FObjectInitializer& ObjectInitializer);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
public:	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = EnemyAnimationClass)
	TSubclassOf<UAnimInstance> EnemyAnimationClass;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = EnemyMesh)
	USkeletalMesh* EnemySkeletalMesh;
	
};
