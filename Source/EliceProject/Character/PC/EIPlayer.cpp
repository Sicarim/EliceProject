// Fill out your copyright notice in the Description page of Project Settings.

#include "../PC/EIPlayer.h"

#include "Camera/CameraComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "Character/Controller/EIPlayerController.h"

#include "Kismet/KismetSystemLibrary.h"

AEIPlayer::AEIPlayer()
{
	//Camera Setting
	m_MainCameraArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("MainCameraArm"));
	if (nullptr != m_MainCameraArm)
		m_MainCameraArm->SetupAttachment(GetCapsuleComponent());

	m_MainCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("MainCamera"));
	if (nullptr != m_MainCamera)
		m_MainCamera->SetupAttachment(m_MainCameraArm);

	m_MainCameraArm->TargetArmLength = 300.0f;
	m_MainCameraArm->SetRelativeRotation(FRotator(-15.0f, 0.0f, 0.0f));
	m_ArmLengthTo = 0.0f;
}

void AEIPlayer::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

void AEIPlayer::BeginPlay()
{
    Super::BeginPlay();

    m_PlayerController = Cast<AEIPlayerController>(GetController());
    if (nullptr == m_PlayerController || false == m_PlayerController->IsValidLowLevel())
        return;

	SetCameraMode();
}

void AEIPlayer::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

	FVector StartPoint = GetActorLocation() + (0.f, 0.f, 50.f);
	FVector EndPoint = GetActorLocation() + (0.f, 0.f, -200.f);
	FHitResult HitResult;
	FVector HitPoint = FVector::ZeroVector;

	TArray<AActor*> IgnoreActors;
	bool Result = UKismetSystemLibrary::LineTraceSingleByProfile(this, StartPoint, EndPoint, TEXT("BlockAll"), false, IgnoreActors, EDrawDebugTrace::None, HitResult, true);
	if (Result == true)
	{
		HitPoint = HitResult.ImpactPoint;
		EI_LOG(Warning, TEXT("asdasdasd : %s"), *HitResult.GetActor()->GetName());
	}
}

void AEIPlayer::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

//----------------------------Public----------------------------//
void AEIPlayer::SetCameraMode()
{
	if (nullptr == m_MainCamera || false == m_MainCamera->IsValidLowLevel())
		return;
	if (nullptr == m_MainCameraArm || false == m_MainCameraArm->IsValidLowLevel())
		return;
	if (nullptr == GetCharacterMovement() || false == GetCharacterMovement()->IsValidLowLevel())
		return;

	m_MainCamera->FieldOfView = 90.f;
	m_ArmLengthTo = 500.f;
	m_MainCamera->SetRelativeLocationAndRotation(FVector(0.0f, 80.0f, 80.0f), FRotator(-3.0f, 0.0f, 0.0f));

	m_MainCameraArm->bUsePawnControlRotation = true;
	m_MainCameraArm->bInheritPitch = true;
	m_MainCameraArm->bInheritRoll = true;
	m_MainCameraArm->bInheritYaw = true;
	m_MainCameraArm->bDoCollisionTest = true;

	m_MainCameraArm->TargetArmLength = m_ArmLengthTo;
}
//--------------------------Public_END--------------------------//

//----------------------------Protected----------------------------//

//--------------------------Protected_END--------------------------//


//----------------------------Private----------------------------//

//--------------------------Private_END--------------------------//