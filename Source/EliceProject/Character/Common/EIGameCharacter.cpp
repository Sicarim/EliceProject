// Fill out your copyright notice in the Description page of Project Settings.

#include "../Common/EIGameCharacter.h"

#include "../../Component/Character/EICharacterMovementComponent.h"

#include "Interaction/Component/EIInteractionComponent.h"

AEIGameCharacter::AEIGameCharacter()
{
	m_InteractionComponent = CreateDefaultSubobject<UEIInteractionComponent>(TEXT("CharacterInteractionComponent"));

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

	InitCharacter();
	//m_PlayerController = GetController();
}

void AEIGameCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

}

//----------------------------Public----------------------------//

//--------------------------Public_END--------------------------//

//----------------------------Protected----------------------------//
void AEIGameCharacter::InitCharacter()
{
	//Interaction
	if (nullptr == m_InteractionComponent || false == m_InteractionComponent->IsValidLowLevel())
		return;

	m_InteractionComponent->SetInteractionOwnerType(EIInteractionOwnerType::Interaction_Doer);
	m_InteractionComponent->SetInteractionObjectType(EIInteractionObjectType::Character);
}
//--------------------------Protected_END--------------------------//


//----------------------------Private----------------------------//

//--------------------------Private_END--------------------------//