// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Manager/EnemyAnimManager/CustomEnemyAccessoryAsset.h"
#include "SoundHorrorGameIdeaCharacter.generated.h"


UCLASS(Blueprintable)
class ASoundHorrorGameIdeaCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ASoundHorrorGameIdeaCharacter();

	// Called every frame.
	virtual void Tick(float DeltaSeconds) override;

	/** Returns TopDownCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetTopDownCameraComponent() const { return TopDownCameraComponent; }
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

private:
	/** Top down camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* TopDownCameraComponent;

	/** Camera boom positioning the camera above the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Accessory)
	TArray<UCustomEnemyAccessoryAsset*> StoredCustomPlayerAccessoryAssets;

	/** 
	* Spawn the accessory mesh and attach it to the specified socket.
	*/
	UFUNCTION(BlueprintCallable, Category = Accessory)
	void SpawnAndAttachAccessories(USkeletalMeshComponent* SkeletalMeshComponent) const;
};

