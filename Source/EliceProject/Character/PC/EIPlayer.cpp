// Fill out your copyright notice in the Description page of Project Settings.

#include "../PC/EIPlayer.h"

#include "Camera/CameraComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "Character/Controller/EIPlayerController.h"

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
	m_ArmLengthTo = 200.f;
	m_MainCamera->SetRelativeLocationAndRotation(FVector(0.0f, 80.0f, 80.0f), FRotator(-3.0f, 0.0f, 0.0f));

	m_MainCameraArm->bUsePawnControlRotation = true;
	m_MainCameraArm->bInheritPitch = true;
	m_MainCameraArm->bInheritRoll = true;
	m_MainCameraArm->bInheritYaw = true;
	m_MainCameraArm->bDoCollisionTest = true;
}
//--------------------------Public_END--------------------------//

//----------------------------Protected----------------------------//

//--------------------------Protected_END--------------------------//


//----------------------------Private----------------------------//

//--------------------------Private_END--------------------------//