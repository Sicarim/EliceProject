// Fill out your copyright notice in the Description page of Project Settings.

#include "../Common/EIGameCharacter.h"

#include "Interaction/Interface/EIInteraction.h"

#include "Interaction/Interface/EIInteractionEnum.h"

#include "Interaction/Component/EIInteractionComponent.h"
#include "Component/Character/EICharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"

#include "Interaction/Actor/EIInteractionBaseActor.h"

AEIGameCharacter::AEIGameCharacter()
{
	m_InteractionComponent = CreateDefaultSubobject<UEIInteractionComponent>(TEXT("CharacterInteractionComponent"));
	if (m_InteractionComponent != nullptr)
	{
		m_InteractionComponent->SetInteractionOwnerType(EIInteractionOwnerType::Interaction_Doer);
	}

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

//* ĳ���� ��ġ�� Set�Ҷ�, ĸ�� ũ�⸸ŭ �ø���. */
void AEIGameCharacter::SetActorNavLocation(FVector InLocation)
{
	FVector OnrigineLocation = InLocation;
	float HalfHeight = GetCapsuleComponent()->GetScaledCapsuleHalfHeight();
	OnrigineLocation += FVector(0.f, 0.f, HalfHeight);

	SetActorLocation(OnrigineLocation);
}

//* ���ͷ��� ���� ���� */
void AEIGameCharacter::Server_ExecuteInteractionEvent_Implementation(AActor* InInteractionCharacter, AActor* InInteractionActor, EIInteractionEventType InEventType)
{
	if (nullptr == InInteractionCharacter || false == InInteractionCharacter->IsValidLowLevel())
	{
		EI_LOG(Warning, TEXT("InInteractionCharacter is nullptr"));
		return;
	}

	if (nullptr == InInteractionActor || false == InInteractionActor->IsValidLowLevel())
	{
		EI_LOG(Warning, TEXT("InInteractionActor is nullptr"));
		return;
	}

	if (nullptr == m_InteractionComponent || false == m_InteractionComponent->IsValidLowLevel())
		return;

	m_InteractionComponent->OnInsertionInteractionData(InInteractionActor, InEventType);

	//ĳ���� - ���ͷ��� ������ ����
	Execute_Interaction_CallEvent(this, InInteractionActor, InEventType);
	Execute_Interaction_CallEvent(InInteractionActor, this, InEventType);
}

//* ���ͷ��� Ŭ�� ���� */
void AEIGameCharacter::Client_ExecuteInteractionEvent_Implementation(AActor* InInteractionCharacter, AActor* InInteractionActor, EIInteractionEventType InEventType)
{
	if (InInteractionCharacter == this)
		Interaction_EventProcess_Implementation(InInteractionActor, InEventType);
	else
	{
		AEIInteractionBaseActor* InteractionActor = Cast<AEIInteractionBaseActor>(InInteractionCharacter);
		if (nullptr == InteractionActor || false == InteractionActor->IsValidLowLevel())
			return;

		InteractionActor->Interaction_EventProcess_Implementation(InInteractionActor, InEventType);
	}
}

//���ͷ��� ȣ�� ����
void AEIGameCharacter::Interaction_CallEvent_Implementation(AActor* InActor, EIInteractionEventType InEventType)
{
	//if (nullptr == m_InteractionComponent || false == m_InteractionComponent->IsValidLowLevel())
	//	return;
	//
	//AEIInteractionBaseActor* InteractionActor = Cast<AEIInteractionBaseActor>(InActor);
	//if (nullptr == InteractionActor || false == InteractionActor->IsValidLowLevel())
	//	return;

	//UEIInteractionComponent* Comp = InteractionActor->GetInteractionComponent();
	//if (nullptr == Comp || false == Comp->IsValidLowLevel())
	//	return;

	//EIInteractionOperateType OperateType = Comp->GetInteractionOperateType();
	//switch (OperateType)
	//{
	//	//Ŭ�� ����
	//case EIInteractionOperateType::OnClient:	
	//	Client_ExecuteInteractionEvent(this, InActor, InEventType);
	//	break;

	//	//���� ����
	//case EIInteractionOperateType::OnServer:
	//	Interaction_EventProcess_Implementation(InActor, InEventType);
	//	break;

	//default:	break;
	//}

	Client_ExecuteInteractionEvent(this, InActor, InEventType);
}

//* ���ͷ��� �̺�Ʈ ���� */
void AEIGameCharacter::Interaction_EventProcess_Implementation(AActor* InActor, EIInteractionEventType InEventType)
{
	if (nullptr == m_InteractionComponent || false == m_InteractionComponent->IsValidLowLevel())
		return;

	//������ ����ȭ
	

	/*ENetMode NetMode = GetNetMode();
	if (ENetMode::NM_Client == NetMode)
	{
		EI_LOG(Warning, TEXT("Client"));
	}
	if (ENetMode::NM_DedicatedServer == NetMode)
	{
		EI_LOG(Warning, TEXT("Server"));
	}*/

	switch (InEventType)
	{
	case EIInteractionEventType::BeginOverlap:		Interaction_BeginOverlap_Implementation(InActor);	break;
	case EIInteractionEventType::Execute:			Interaction_Execute_Implementation(InActor);		break;
	case EIInteractionEventType::EndOverlap:		Interaction_EndOverlap_Implementation(InActor);		break;
	default:																							break;
	}

	Interaction_EventCompliete_Implementation(InActor, InEventType);
}

bool AEIGameCharacter::IsEnableInteraction_Implementation(AActor* InActor, EIInteractionEventType InEventType)
{
	return false;
}

void AEIGameCharacter::Interaction_EventCompliete_Implementation(AActor* InActor, EIInteractionEventType InEventType)
{
	if (nullptr == m_InteractionComponent || false == m_InteractionComponent->IsValidLowLevel())
		return;

	m_InteractionComponent->OnInsertionInteractionData(InActor, InEventType);

	switch (InEventType)
	{
	case EIInteractionEventType::BeginOverlap:		break;
	case EIInteractionEventType::Execute:			break;
	case EIInteractionEventType::EndOverlap:		m_InteractionComponent->OnRemoveInteractionData(InActor);		break;
	default:																										break;
	}
}

void AEIGameCharacter::Interaction_BeginOverlap_Implementation(AActor* InActor)
{
	
}

void AEIGameCharacter::Interaction_Execute_Implementation(AActor* InActor)
{

}

void AEIGameCharacter::Interaction_EndOverlap_Implementation(AActor* InActor)
{

}
//----------------------------Public----------------------------//

//--------------------------Public_END--------------------------//

//----------------------------Protected----------------------------//
void AEIGameCharacter::InitCharacter()
{
	if (GetMesh() != nullptr && GetMesh()->IsValidLowLevel() == true)
	{
		//Mesh Collision off
		GetMesh()->SetCollisionProfileName(TEXT("NoCollision"));
		//ī�� ������ On
		GetMesh()->SetRenderCustomDepth(true);
	}

	//Interaction
	if (nullptr == m_InteractionComponent || false == m_InteractionComponent->IsValidLowLevel())
		return;

	m_InteractionComponent->SetInteractionOwnerType(EIInteractionOwnerType::Interaction_Doer);
	m_InteractionComponent->SetInteractionObjectType(EIInteractionObjectType::Character);
}
//--------------------------Protected_END--------------------------//


//----------------------------Private----------------------------//

//--------------------------Private_END--------------------------//