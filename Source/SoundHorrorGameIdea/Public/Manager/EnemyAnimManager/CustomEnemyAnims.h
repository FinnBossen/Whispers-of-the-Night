#pragma once
#include "CustomEnemyAccessory.h"
#include "JumpScareAnim.h"
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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Accessory)
	TArray<UCustomEnemyAccessory*> StoredCustomEnemyAccessory;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = JumpScareAnim)
	UJumpScareAnim* JumpScareAnim;

	/** 
  * Spawn the accessory mesh and attach it to the specified socket.
  */
	UFUNCTION(BlueprintCallable, Category = Accessory)
	void SpawnAndAttachAccessories(USkeletalMeshComponent* SkeletalMeshComponent, AActor* Owner) const;
};
