// Fill out your copyright notice in the Description page of Project Settings.

#include "Interaction/Actor/EIInteractionBaseActor.h"

#include "Interaction/Component/EIInteractionComponent.h"

AEIInteractionBaseActor::AEIInteractionBaseActor()
{
	m_InteractionComponent = CreateDefaultSubobject<UEIInteractionComponent>(TEXT("BaseActorInteractionComponent"));
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

//--------------------------Public_END--------------------------//

//----------------------------Protected----------------------------//
void AEIInteractionBaseActor::InitInteraction()
{
	if (nullptr == m_InteractionComponent || false == m_InteractionComponent->IsValidLowLevel())
		return;
	
	m_InteractionComponent->SetInteractionOwnerType(EIInteractionOwnerType::Interaction_Doer);
	
	
}
//--------------------------Protected_END--------------------------//


//----------------------------Private----------------------------//

//--------------------------Private_END--------------------------//