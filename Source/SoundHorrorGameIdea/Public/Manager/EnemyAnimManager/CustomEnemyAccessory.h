// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CustomEnemyAccessory.generated.h"


UCLASS(EditInlineNew, blueprintable)
class UCustomEnemyAccessory : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UCustomEnemyAccessory();

	/**
	* Spawn the accessory mesh and attach it to the specified socket.
	*/
	UFUNCTION(BlueprintCallable, Category = Accessory)
	void SpawnAccessoryAtSocket(USkeletalMeshComponent* SkeletalMeshComponent, AActor* Owner) const;

	/**
* Spawn the accessory mesh and attach it to the specified socket.
*/
	UFUNCTION(BlueprintCallable, Category = Accessory)
	void SpawnAccessoryAtSocketWithoutShadow(USkeletalMeshComponent* SkeletalMeshComponent, AActor* Owner) const;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AccessoireMesh)
	UStaticMesh* AccessoryMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AccessoireSocket)
	FName AccessorySocketName;
};
