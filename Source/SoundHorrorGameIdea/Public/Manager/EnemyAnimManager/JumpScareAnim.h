// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "JumpScareAnim.generated.h"


class UCameraComponent;

UCLASS(EditInlineNew, blueprintable)
class SOUNDHORRORGAMEIDEA_API UJumpScareAnim : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UJumpScareAnim();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	void ToggleCamera(const AActor* Player);

	void CreateCameraAndPutInToSocket();

	static TArray<UCameraComponent*> GetAllCameraComponents(const AActor* Actor);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera)
	UCameraComponent* JumpScareCamera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera)
	UCameraComponent* PreviousCamera;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera)
	bool IsCameraActive = false;

public:	

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
	UAnimMontage* JumpScareAnim;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera)
	FName CameraSocketName;

	UFUNCTION(BlueprintCallable, Category = Animation)
	void PlayJumpScareAnim(USkeletalMeshComponent* SkeletalMeshComponent, AActor* Owner, AActor* Player);
	
	// This function will be called when the JumpScareAnim animation ends
	UFUNCTION()
	void OnJumpScareAnimEnded(UAnimMontage* Montage, bool bInterrupted);
};






