// Fill out your copyright notice in the Description page of Project Settings.

#include "Interaction/Actor/InteractionBaseActor.h"

#include "Interaction/Component/EIInteractionComponent.h"

AInteractionBaseActor::AInteractionBaseActor()
{
	PrimaryActorTick.bCanEverTick = true;

	m_InteractionComponent = CreateDefaultSubobject<UEIInteractionComponent>(TEXT("InteractionComponent"));
}

void AInteractionBaseActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void AInteractionBaseActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}