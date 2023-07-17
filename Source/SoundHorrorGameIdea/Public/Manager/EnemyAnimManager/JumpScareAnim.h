#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "JumpScareAnim.generated.h"

class UCameraComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnMontageEndedDelegate, UAnimMontage*, Montage, bool, bInterrupted);

UCLASS(EditInlineNew, blueprintable)
class SOUNDHORRORGAMEIDEA_API UJumpScareAnim : public UActorComponent
{
	GENERATED_BODY()

public:	
	UJumpScareAnim();

protected:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void ToggleCamera(const AActor* Player);
	static TArray<UCameraComponent*> GetAllCameraComponents(const AActor* Actor);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera)
	UCameraComponent* JumpScareCamera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera)
	UCameraComponent* PreviousCamera;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera)
	bool IsCameraActive = false;

public:
	UFUNCTION(BlueprintCallable, Category = Animation)
	void PutCameraIntoSocket(UCameraComponent* CameraComponent, USkeletalMeshComponent* OwnerSkeletalMeshComponent);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
	UAnimMontage* JumpScareAnim;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera)
	FName CameraSocketName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera)
	FName HeadSocketName;

	UPROPERTY()
	USkeletalMeshSocket* HeadSocket;

	UPROPERTY()
	USkeletalMeshComponent* AttachedSkeletonMeshOwner;

	UFUNCTION(BlueprintCallable, Category = Animation)
	void PlayJumpScareAnim(USkeletalMeshComponent* SkeletalMeshComponent,  AActor* Player);

	// This function will be called when the JumpScareAnim animation ends
	UFUNCTION()
	void OnJumpScareAnimEnded(UAnimMontage* Montage, bool bInterrupted);

	FOnMontageEndedDelegate OnMontageEndedDelegate;
};
