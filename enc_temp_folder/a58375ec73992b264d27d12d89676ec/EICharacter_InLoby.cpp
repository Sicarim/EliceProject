// Fill out your copyright notice in the Description page of Project Settings.

#include "Character/PC/EICharacter_InLoby.h"

#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"

#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/SkeletalMeshComponent.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "Character/Controller/EIPlayerController_InLoby.h"

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

	APlayerController* PC = UGameplayStatics::GetPlayerController(this, 0);
	if (PC == nullptr || PC->IsValidLowLevel() == false)
		return;

	m_PlayerController = Cast<AEIPlayerController_InLoby>(PC);
	if (nullptr == m_PlayerController || false == m_PlayerController->IsValidLowLevel())
		return;

	SetCameraMode();
}

void AEICharacter_InLoby::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

void AEICharacter_InLoby::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	EI_LOG(Warning, TEXT("Pitch : %f		Yaw : %f		Roll : %f"), m_LobyCamera->GetRelativeRotation().Pitch, m_LobyCamera->GetRelativeRotation().Yaw, m_LobyCamera->GetRelativeRotation().Roll);

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
	m_LobyCamera->SetRelativeLocationAndRotation(FVector(0.0f, 10.f, 50.f), FRotator(-3.0f, 0.0f, 0.0f));
	//(X = -0, Y = -5.000007, Z = 4.000000)

	m_LobyCameraArm->SetWorldRotation(FRotator(-14.0f, -170.0f, 0.0f));
	m_LobyCameraArm->bUsePawnControlRotation = false;
	m_LobyCameraArm->bInheritPitch = false;
	m_LobyCameraArm->bInheritRoll = false;
	m_LobyCameraArm->bInheritYaw = false;
	m_LobyCameraArm->bDoCollisionTest = false;
}