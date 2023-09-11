#include "Manager/EnemyAnimManager/JumpScareAnim.h"
#include "Camera/CameraComponent.h"
#include "Engine/SkeletalMeshSocket.h"
#include "GameFramework/Character.h"
#include "AIController.h"

UJumpScareAnim::UJumpScareAnim()
{
    PrimaryComponentTick.bCanEverTick = true;
}

void UJumpScareAnim::BeginPlay()
{
    Super::BeginPlay();
}

void UJumpScareAnim::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
    
    if(IsCameraActive && JumpScareCamera && HeadSocket)
    {
        if (const USkeletalMeshComponent* SkeletalMeshComponent = AttachedSkeletonMeshOwner)
        {
            const FVector HeadLocation = HeadSocket->GetSocketLocation(SkeletalMeshComponent);
            const FVector LookAtDirection = (HeadLocation - JumpScareCamera->GetComponentLocation()).GetSafeNormal();
            const FRotator LookAtRotation = LookAtDirection.Rotation();
            JumpScareCamera->SetWorldRotation(LookAtRotation);
        }
    }
}

void UJumpScareAnim::ToggleCamera(const AActor* Player)
{
    TArray<UCameraComponent*> CameraComponents = GetAllCameraComponents(Player);
    for (UCameraComponent* CameraComponent : CameraComponents)
    {
        if (IsCameraActive)
        {
            if (PreviousCamera)
            {
                PreviousCamera->SetActive(true);
            }
        }
        else
        {
            if (CameraComponent->IsActive())
            {
                PreviousCamera = CameraComponent;
            }
            CameraComponent->SetActive(false);
        }
    }

    if (JumpScareCamera)
    {
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

    if (CameraComponent)
    {
        JumpScareCamera = CameraComponent;
        JumpScareCamera->RegisterComponent();
        JumpScareCamera->AttachToComponent(CameraComponent, FAttachmentTransformRules::SnapToTargetIncludingScale, CameraSocketName);
        JumpScareCamera->SetActive(false);
    }
    
    if (const USkeletalMeshComponent* SkeletalMeshComponent = Cast<USkeletalMeshComponent>(OwnerSkeletalMeshComponent))
    {
        HeadSocket = const_cast<USkeletalMeshSocket*>(SkeletalMeshComponent->GetSocketByName(HeadSocketName));
    }
}

TArray<UCameraComponent*> UJumpScareAnim::GetAllCameraComponents(const AActor* Actor)
{
    TArray<UCameraComponent*> CameraComponents;

    if (Actor)
    {
        Actor->GetComponents<UCameraComponent>(CameraComponents);
    }

    return CameraComponents;
}

void UJumpScareAnim::PlayJumpScareAnim(USkeletalMeshComponent* SkeletalMeshComponent, ACharacter* Enemy, ACharacter* Player)
{
    // Store the enemy and player characters
    EnemyCharacter = Enemy;
    PlayerCharacter = Player;
    /*
    if(AIController* AI = Cast<AAIController>(Enemy->GetController()))
    {
        AI->StopMovement();
    }
    */

    if (ACharacter* CharacterPlayer = Cast<ACharacter>(Player))
    {
        if (APlayerController* PlayerController = Cast<APlayerController>(CharacterPlayer->GetController()))
        {
            PlayerController->SetIgnoreMoveInput(true);
        }
    }
    // ToggleCamera(Player);
    if (UAnimInstance* AnimInstance = SkeletalMeshComponent->GetAnimInstance(); AnimInstance && JumpScareAnim)
    {
        //FOnMontageEnded MontageEndedDelegateLocal;
        //MontageEndedDelegateLocal.BindUObject(this, &UJumpScareAnim::OnJumpScareAnimEnded);
        AnimInstance->Montage_Play(JumpScareAnim);
        //AnimInstance->Montage_SetEndDelegate(MontageEndedDelegateLocal, JumpScareAnim);
    }
}

void UJumpScareAnim::OnJumpScareAnimEnded(UAnimMontage* Montage, bool bInterrupted)
{
    JumpScareCamera->SetActive(false);
    
    if (IsCameraActive)
    {
        if (PreviousCamera)
        {
            PreviousCamera->SetActive(true);
        }
    }

    IsCameraActive = false;
/*
    if(AIController* AI = Cast<AAIController>(EnemyCharacter->GetController()))
    {
        AI->MoveToActor(Player, 5.0f, true, true, true, 0, true);
    }
    */
    if (const ACharacter* CharacterPlayer = Cast<ACharacter>(PlayerCharacter))
    {
        if (APlayerController* PlayerController = Cast<APlayerController>(CharacterPlayer->GetController()))
        {
            PlayerController->SetIgnoreMoveInput(false);
        }
    }
    
}
