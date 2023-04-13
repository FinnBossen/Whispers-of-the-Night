// Copyright Epic Games, Inc. All Rights Reserved.

#include "Controller/SoundHorrorGameIdeaPlayerController.h"

#include "GameFramework/Pawn.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "NiagaraFunctionLibrary.h"
#include "SoundHorrorGameIdea/Public/Character/SoundHorrorGameIdeaCharacter.h"
#include "Engine/World.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/Controller.h"
#include "Kismet/KismetMathLibrary.h"

ASoundHorrorGameIdeaPlayerController::ASoundHorrorGameIdeaPlayerController()
{
	bShowMouseCursor = false;
	DefaultMouseCursor = EMouseCursor::Default;
	CachedDestination = FVector::ZeroVector;
	FollowTime = 0.f;
	MovementSpeed = 1.f;
}

void ASoundHorrorGameIdeaPlayerController::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	LastMouseRotation = FRotator(0, 0, 0);

	//Add Input Mapping Context
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(
		GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(DefaultMappingContext, 0);
	}
}

FRotator ASoundHorrorGameIdeaPlayerController::GetMouseRotation() const
{
	return LastMouseRotation;
}

void ASoundHorrorGameIdeaPlayerController::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();

	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent))
	{
		//Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this,
		                                   &ASoundHorrorGameIdeaPlayerController::Move);


		//Rotating
		EnhancedInputComponent->BindAction(MouseRotateAction, ETriggerEvent::Triggered, this,
		                                   &ASoundHorrorGameIdeaPlayerController::OnRotateToMouse);


		// Setup mouse input events
		EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Started, this,
		                                   &ASoundHorrorGameIdeaPlayerController::OnInputStarted);
		EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Triggered, this,
		                                   &ASoundHorrorGameIdeaPlayerController::OnSetDestinationTriggered);
		EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Completed, this,
		                                   &ASoundHorrorGameIdeaPlayerController::OnSetDestinationReleased);
		EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Canceled, this,
		                                   &ASoundHorrorGameIdeaPlayerController::OnSetDestinationReleased);

		// Setup touch input events
		EnhancedInputComponent->BindAction(SetDestinationTouchAction, ETriggerEvent::Started, this,
		                                   &ASoundHorrorGameIdeaPlayerController::OnInputStarted);
		EnhancedInputComponent->BindAction(SetDestinationTouchAction, ETriggerEvent::Triggered, this,
		                                   &ASoundHorrorGameIdeaPlayerController::OnTouchTriggered);
		EnhancedInputComponent->BindAction(SetDestinationTouchAction, ETriggerEvent::Completed, this,
		                                   &ASoundHorrorGameIdeaPlayerController::OnTouchReleased);
		EnhancedInputComponent->BindAction(SetDestinationTouchAction, ETriggerEvent::Canceled, this,
		                                   &ASoundHorrorGameIdeaPlayerController::OnTouchReleased);
	}
}

void ASoundHorrorGameIdeaPlayerController::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	const FVector2D MovementVector = Value.Get<FVector2D>();


	// find out which way is forward
	const FRotator Rotation = this->GetControlRotation();
	const FRotator YawRotation(0, Rotation.Yaw, 0);

	// get forward vector
	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

	// get right vector 
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	// add movement 
	if (APawn* ControlledPawn = GetPawn(); ControlledPawn != nullptr)
	{
		ControlledPawn->AddMovementInput(ForwardDirection * MovementSpeed, MovementVector.Y * MovementSpeed);
		ControlledPawn->AddMovementInput(RightDirection * MovementSpeed, MovementVector.X * MovementSpeed);
		if (const ACharacter* CharacterFromController = GetCharacter(); CharacterFromController != nullptr)
		{
			CharacterFromController->GetMesh()->SetWorldRotation(LastMouseRotation);
		}
	}
}

void ASoundHorrorGameIdeaPlayerController::OnRotateToMouse(const FInputActionValue& Value)
{
	if (const APawn* ControlledPawn = GetPawn(); ControlledPawn != nullptr)
	{
		const FVector ActorLocation = ControlledPawn->GetActorLocation();
		const FVector Actor2D = FVector(ActorLocation.X, ActorLocation.Y, 0);
		const FVector2D MouseVector = Value.Get<FVector2D>();
		const FVector MouseValueWithActorPosition = FVector(ActorLocation.X + MouseVector.X,
		                                                    ActorLocation.Y + MouseVector.Y, 0);

		const FRotator RotateTo = UKismetMathLibrary::FindLookAtRotation(Actor2D, MouseValueWithActorPosition);
		if (const ACharacter* CharacterFromController = GetCharacter(); CharacterFromController != nullptr)
		{
			LastMouseRotation = RotateTo.GetInverse();
			CharacterFromController->GetMesh()->SetWorldRotation(LastMouseRotation);
		}
	}
}

void ASoundHorrorGameIdeaPlayerController::OnInputStarted()
{
	StopMovement();
}

// Triggered every frame when the input is held down
void ASoundHorrorGameIdeaPlayerController::OnSetDestinationTriggered()
{
	// We flag that the input is being pressed
	FollowTime += GetWorld()->GetDeltaSeconds();

	// We look for the location in the world where the player has pressed the input
	FHitResult Hit;
	bool bHitSuccessful;
	if (bIsTouch)
	{
		bHitSuccessful = GetHitResultUnderFinger(ETouchIndex::Touch1, ECollisionChannel::ECC_Visibility, true, Hit);
	}
	else
	{
		bHitSuccessful = GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, true, Hit);
	}

	// If we hit a surface, cache the location
	if (bHitSuccessful)
	{
		CachedDestination = Hit.Location;
	}

	// Move towards mouse pointer or touch
	APawn* ControlledPawn = GetPawn();
	if (ControlledPawn != nullptr)
	{
		FVector WorldDirection = (CachedDestination - ControlledPawn->GetActorLocation()).GetSafeNormal();
		ControlledPawn->AddMovementInput(WorldDirection, 1.0, false);
	}
}

void ASoundHorrorGameIdeaPlayerController::OnSetDestinationReleased()
{
	// If it was a short press
	if (FollowTime <= ShortPressThreshold)
	{
		// We move there and spawn some particles
		UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, CachedDestination);
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, FXCursor, CachedDestination, FRotator::ZeroRotator,
		                                               FVector(1.f, 1.f, 1.f), true, true, ENCPoolMethod::None, true);
	}

	FollowTime = 0.f;
}

// Triggered every frame when the input is held down
void ASoundHorrorGameIdeaPlayerController::OnTouchTriggered()
{
	bIsTouch = true;
	OnSetDestinationTriggered();
}

void ASoundHorrorGameIdeaPlayerController::OnTouchReleased()
{
	bIsTouch = false;
	OnSetDestinationReleased();
}
