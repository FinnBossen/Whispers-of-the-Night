// Fill out your copyright notice in the Description page of Project Settings.

#include "Manager/EnemyAnimManager/JumpScareAnim.h"

#include "Camera/CameraComponent.h"

// Sets default values for this component's properties
UJumpScareAnim::UJumpScareAnim()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UJumpScareAnim::BeginPlay()
{
	Super::BeginPlay();

	CreateCameraAndPutInToSocket();
	
}

void UJumpScareAnim::ToggleCamera(const AActor* Player)
{
	// Get all camera components of the player
	TArray<UCameraComponent*> CameraComponents = GetAllCameraComponents(Player);

	// Loop through all camera components and set the active state
	for (UCameraComponent* CameraComponent : CameraComponents)
	{
		// if camera is active then activate the cameraComponent
		if (IsCameraActive)
		{
			// Check if PreviousCamera is valid
			if (PreviousCamera)
			{
				PreviousCamera->SetActive(true);
			}
		}
		else
		{
			// Check if CameraComponent is active
			if (CameraComponent->IsActive())
			{
				// Set the PreviousCamera to the CameraComponent
				PreviousCamera = CameraComponent;
			}
			CameraComponent->SetActive(false);
		}
	}

	// check if the JumpScareCamera is valid
	if (JumpScareCamera)
	{
		// Set the active state of the JumpScareCamera
		JumpScareCamera->SetActive(!IsCameraActive);
	}

	IsCameraActive = !IsCameraActive;
}

void UJumpScareAnim::CreateCameraAndPutInToSocket()
{
	// Create the JumpScareCamera and put into the owner socket with scale and rotation
	JumpScareCamera = NewObject<UCameraComponent>(GetOwner(), UCameraComponent::StaticClass(), CameraSocketName);
}

TArray<UCameraComponent*> UJumpScareAnim::GetAllCameraComponents(const AActor* Actor)
{
	TArray<UCameraComponent*> CameraComponents;

	if (Actor)
	{
		// Get all camera components of the actor
		Actor->GetComponents<UCameraComponent>(CameraComponents);
	}

	// Return the array of camera components
	return CameraComponents;
}

void UJumpScareAnim::PlayJumpScareAnim(USkeletalMeshComponent* SkeletalMeshComponent, AActor* Owner, AActor* Player)
{
	ToggleCamera(Player);
	// Play the JumpScareAnim on the SkeletalMeshComponent
	UAnimInstance* AnimInstance = SkeletalMeshComponent->GetAnimInstance();
	if (AnimInstance && JumpScareAnim)
	{
		FOnMontageEnded MontageEndedDelegate;
		MontageEndedDelegate.BindUFunction(this, FName("OnJumpScareAnimEnded"));
		AnimInstance->Montage_Play(JumpScareAnim);
		AnimInstance->Montage_SetEndDelegate(MontageEndedDelegate, JumpScareAnim);
	}

}

void UJumpScareAnim::OnJumpScareAnimEnded(UAnimMontage* Montage, bool bInterrupted)
{

	JumpScareCamera->SetActive(false);
	
	if (IsCameraActive)
	{
		// Check if PreviousCamera is valid
		if (PreviousCamera)
		{
			PreviousCamera->SetActive(true);
		}
	}

	IsCameraActive = false;
}


