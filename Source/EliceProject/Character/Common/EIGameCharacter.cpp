// Fill out your copyright notice in the Description page of Project Settings.

#include "../Common/EIGameCharacter.h"

#include "../../Component/Character/EICharacterMovementComponent.h"

AEIGameCharacter::AEIGameCharacter()
{
	//CharacterMovementComponent = CreateDefaultSubobject<UEICharacterMovementComponent>(TEXT("EICharacterMovementComponent"));
	//if (nullptr != CharacterMovementComponent)
	//{
	//	/*CharacterMovementComponent->UpdatedComponent = CapsuleComponent;
	//	CrouchedEyeHeight = CharacterMovement->CrouchedHalfHeight * 0.80f;*/
	//}
}

void AEIGameCharacter::BeginPlay()
{
    Super::BeginPlay();
	//m_PlayerController = GetController();
}

void AEIGameCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

}

//----------------------------Public----------------------------//

//--------------------------Public_END--------------------------//

//----------------------------Protected----------------------------//

//--------------------------Protected_END--------------------------//


//----------------------------Private----------------------------//

//--------------------------Private_END--------------------------//