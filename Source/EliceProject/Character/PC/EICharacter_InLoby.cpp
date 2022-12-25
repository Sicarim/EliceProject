// Fill out your copyright notice in the Description page of Project Settings.

#include "Character/PC/EICharacter_InLoby.h"

#include "Camera/CameraComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

AEICharacter_InLoby::AEICharacter_InLoby()
{
	//Camera Setting
	m_LobyCameraArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("LobyCameraArm"));
	if (nullptr != m_LobyCameraArm)
		m_LobyCameraArm->SetupAttachment(GetCapsuleComponent());

	m_LobyCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("LobyCamera"));
	if (nullptr != m_LobyCamera)
		m_LobyCamera->SetupAttachment(m_LobyCameraArm);

	m_LobyCameraArm->TargetArmLength = 300.0f;
	m_LobyCameraArm->SetRelativeRotation(FRotator(-15.0f, 0.0f, 0.0f));
	m_ArmLengthTo = 0.0f;
}

void AEICharacter_InLoby::BeginPlay()
{
	Super::BeginPlay();

	SetCameraMode();
}

void AEICharacter_InLoby::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

void AEICharacter_InLoby::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEICharacter_InLoby::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AEICharacter_InLoby::SetCameraMode()
{
	if (nullptr == m_LobyCamera || false == m_LobyCamera->IsValidLowLevel())
		return;
	if (nullptr == m_LobyCameraArm || false == m_LobyCameraArm->IsValidLowLevel())
		return;

	m_LobyCamera->FieldOfView = 90.f;
	m_ArmLengthTo = 200.f;
	m_LobyCamera->SetRelativeLocationAndRotation(FVector(0.0f, 80.0f, 80.0f), FRotator(-3.0f, 0.0f, 0.0f));

	m_LobyCameraArm->bUsePawnControlRotation = true;
	m_LobyCameraArm->bInheritPitch = true;
	m_LobyCameraArm->bInheritRoll = true;
	m_LobyCameraArm->bInheritYaw = true;
	m_LobyCameraArm->bDoCollisionTest = true;
}