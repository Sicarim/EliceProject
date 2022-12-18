// Fill out your copyright notice in the Description page of Project Settings.

#include "Interaction/Actor/EIInteractionBaseActor.h"

#include "Character/Common/EIGameCharacter.h"

#include "Interaction/Component/EIInteractionComponent.h"

AEIInteractionBaseActor::AEIInteractionBaseActor()
{
	InteractionComponent = CreateDefaultSubobject<UEIInteractionComponent>(TEXT("InteractionComponent"));
	if (nullptr != InteractionComponent)
	{
		InteractionComponent->SetInteractionOwnerType(EIInteractionOwnerType::Interaction_Object);
	}
}

void AEIInteractionBaseActor::BeginPlay()
{
	Super::BeginPlay();

	InitInteraction();
}

void AEIInteractionBaseActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
//----------------------------Public----------------------------//
//인터랙션 호출 실행
void AEIInteractionBaseActor::Interaction_CallEvent_Implementation(AActor* InActor, EIInteractionEventType InEventType)
{
	if (nullptr == InteractionComponent || false == InteractionComponent->IsValidLowLevel())
		return;

	EIInteractionOperateType OperateType = InteractionComponent->GetInteractionOperateType();
	switch (OperateType)
	{
		//클라 실행
	case EIInteractionOperateType::OnClient:
	{
		AEIGameCharacter* Character = Cast<AEIGameCharacter>(InActor);
		if (nullptr == Character || false == Character->IsValidLowLevel())
			return;

		Character->Client_ExecuteInteractionEvent(this, InActor, InEventType);
		break;
	}
		//서버 실행
	case EIInteractionOperateType::OnServer:
		Interaction_EventProcess_Implementation(InActor, InEventType);
		break;

	default:	break;
	}
}

//* 인터랙션 이벤트 실행 */
void AEIInteractionBaseActor::Interaction_EventProcess_Implementation(AActor* InActor, EIInteractionEventType InEventType)
{
	if (nullptr == InteractionComponent || false == InteractionComponent->IsValidLowLevel())
		return;

	InteractionComponent->OnInsertionInteractionData(InActor, InEventType);

	switch (InEventType)
	{
	case EIInteractionEventType::BeginOverlap:		Interaction_BeginOverlap_Implementation(InActor);   break;
	case EIInteractionEventType::Execute:			Interaction_Execute_Implementation(InActor);		break;
	case EIInteractionEventType::EndOverlap:		Interaction_EndOverlap_Implementation(InActor);		break;
	default:																							break;
	}

	Interaction_EventCompliete_Implementation(InActor, InEventType);
}

bool AEIInteractionBaseActor::IsEnableInteraction_Implementation(AActor* InActor, EIInteractionEventType InEventType)
{
	if (nullptr == InActor || false == InActor->IsValidLowLevel())
		return false;

	AEIGameCharacter* Character = Cast<AEIGameCharacter>(InActor);
	if (nullptr == Character || false == Character->IsValidLowLevel())
		return false;
	else
		return true;

	return false;
}

void AEIInteractionBaseActor::Interaction_EventCompliete_Implementation(AActor* InActor, EIInteractionEventType InEventType)
{
	if (nullptr == InteractionComponent || false == InteractionComponent->IsValidLowLevel())
		return;

	InteractionComponent->OnInsertionInteractionData(InActor, InEventType);

	switch (InEventType)
	{
	case EIInteractionEventType::BeginOverlap:		break;
	case EIInteractionEventType::Execute:			break;
	case EIInteractionEventType::EndOverlap:		InteractionComponent->OnRemoveInteractionData(InActor);		break;
	default:																										break;
	}
}
//--------------------------Public_END--------------------------//

//----------------------------Protected----------------------------//
//* 인터랙션 클라 실행 */
void AEIInteractionBaseActor::Client_ExecuteEvent_Implementation(AActor* InInteractionCharacter, AActor* InInteractionActor, EIInteractionEventType InEventType)
{
	Interaction_EventProcess_Implementation(InInteractionActor, InEventType);
}

void AEIInteractionBaseActor::InitInteraction()
{
	if (nullptr == InteractionComponent || false == InteractionComponent->IsValidLowLevel())
		return;

	
}

//* Begin Event */
void AEIInteractionBaseActor::Interaction_BeginOverlap_Implementation(AActor* InActor)
{
	UE_LOG(LogTemp, Warning, TEXT("Base Begin"));
}

//* Execute Event */
void AEIInteractionBaseActor::Interaction_Execute_Implementation(AActor* InActor)
{
	UE_LOG(LogTemp, Warning, TEXT("Base Execute"));
}

//* End Event */
void AEIInteractionBaseActor::Interaction_EndOverlap_Implementation(AActor* InActor)
{
	UE_LOG(LogTemp, Warning, TEXT("Base End"));
}

//* Link Event */
void AEIInteractionBaseActor::Interaction_LinkEvent_Implementation(bool InActive)
{

}

void AEIInteractionBaseActor::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

//--------------------------Protected_END--------------------------//


//----------------------------Private----------------------------//

//--------------------------Private_END--------------------------//