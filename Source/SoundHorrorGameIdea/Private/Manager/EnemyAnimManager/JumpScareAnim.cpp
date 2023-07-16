// Fill out your copyright notice in the Description page of Project Settings.

#include "Manager/EnemyAnimManager/JumpScareAnim.h"

#include "Camera/CameraComponent.h"
#include "Chaos/ChaosPerfTest.h"
#include "Engine/SkeletalMeshSocket.h"

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
}

void UJumpScareAnim::TickComponent(const float DeltaTime, const ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	if(IsCameraActive && JumpScareCamera && HeadSocket)
	{
		// Cast the root component to a skeletal mesh component

		if (const USkeletalMeshComponent* SkeletalMeshComponent = AttachedSkeletonMeshOwner)
		{
			// Get the world location of the HeadSocket
			const FVector HeadLocation = HeadSocket->GetSocketLocation(SkeletalMeshComponent);

			// Calculate the direction vector from the camera to the HeadSocket
			const FVector LookAtDirection = (HeadLocation - JumpScareCamera->GetComponentLocation()).GetSafeNormal();

			// Create a rotation based on the direction vector
			const FRotator LookAtRotation = LookAtDirection.Rotation();

			// Set the camera's rotation to the LookAtRotation
			JumpScareCamera->SetWorldRotation(LookAtRotation);
		}
	}
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

void UJumpScareAnim::PutCameraIntoSocket(UCameraComponent* CameraComponent,USkeletalMeshComponent* OwnerSkeletalMeshComponent)
{
	if(!OwnerSkeletalMeshComponent)
	{
		UE_LOG(LogTemp, Error, TEXT("OwnerSkeletalMeshComponent is not valid for JumpScareAnim"));
		return;
	}

	AttachedSkeletonMeshOwner = OwnerSkeletalMeshComponent;
	// Put cameraComponent in to the socket
	if (CameraComponent)
	{
		// Save the JumpScareCamera
		JumpScareCamera = CameraComponent;

		// Register the JumpScareCamera to the game
		JumpScareCamera->RegisterComponent();

		// Attach the JumpScareCamera to the SkeletalMeshComponent on the specified socket
		JumpScareCamera->AttachToComponent(CameraComponent, FAttachmentTransformRules::SnapToTargetIncludingScale, CameraSocketName);

		// Set the active state of the JumpScareCamera
		JumpScareCamera->SetActive(false);
	}
	
	// Assuming the SkeletalMeshComponent is the owner's root component
	if (const USkeletalMeshComponent* SkeletalMeshComponent = Cast<USkeletalMeshComponent>(OwnerSkeletalMeshComponent))
	{
		// Get the HeadSocket by its name
		HeadSocket = const_cast<USkeletalMeshSocket*>(SkeletalMeshComponent->GetSocketByName(HeadSocketName));
	}
	
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


