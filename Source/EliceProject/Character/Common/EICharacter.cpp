// Fill out your copyright notice in the Description page of Project Settings.

#include "../Common/EICharacter.h"

#include "Net/UnrealNetwork.h"

#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

AEICharacter::AEICharacter()
{
	PrimaryActorTick.bCanEverTick = true;

}

void AEICharacter::BeginPlay()
{
	Super::BeginPlay();
	
	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->bUseControllerDesiredRotation = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);
}

void AEICharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEICharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//Base Move Key
	PlayerInputComponent->BindAction(TEXT("Jump"), EInputEvent::IE_Pressed, this, &AEICharacter::Jump);
	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &AEICharacter::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &AEICharacter::MoveRight);
	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &AEICharacter::Turn);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &AEICharacter::LookUp);

	//Interaction Key
	PlayerInputComponent->BindAction(TEXT("Interaction"), EInputEvent::IE_Pressed, this, &AEICharacter::IsInteractionKey);
}

//----------------------------Public----------------------------//
//--------------------------Public_END--------------------------//

//----------------------------Protected----------------------------//
void AEICharacter::IsInteractionKey()
{

}

//이동(앞, 뒤)
void AEICharacter::MoveForward(float InAxisValue)
{
	if (true == FMath::IsNearlyEqual(InAxisValue, -1.f) || true == FMath::IsNearlyEqual(InAxisValue, 1.f))
		m_IsFoward = true;
	else
		m_IsFoward = false;

	const FRotator Rotation = Controller->GetControlRotation();
	const FRotator YawRotation(0, Rotation.Yaw, 0);
	const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

	AddMovementInput(Direction, InAxisValue);
}

//이동(좌, 우)
void AEICharacter::MoveRight(float InAxisValue)
{
	if (true == FMath::IsNearlyEqual(InAxisValue, -1.f) || true == FMath::IsNearlyEqual(InAxisValue, 1.f))
		m_IsRight = true;
	else
		m_IsRight = false;

	const FRotator Rotation = Controller->GetControlRotation();
	const FRotator YawRotation(0, Rotation.Yaw, 0);
	const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	
	AddMovementInput(Direction, InAxisValue);
}

void AEICharacter::LookUp(float InAxisValue)
{
	AddControllerPitchInput(InAxisValue * m_BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void AEICharacter::Turn(float InAxisValue)
{
	AddControllerYawInput(InAxisValue * m_BaseTurnRate * GetWorld()->GetDeltaSeconds());
}
//--------------------------Protected_END--------------------------//

//----------------------------Private----------------------------//
//--------------------------Private_END--------------------------//