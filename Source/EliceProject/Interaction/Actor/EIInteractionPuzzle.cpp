// Fill out your copyright notice in the Description page of Project Settings.

#include "Interaction/Actor/EIInteractionPuzzle.h"

#include "Components/BoxComponent.h"

AEIInteractionPuzzle::AEIInteractionPuzzle()
{
    m_BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("PuzzleBoxCollision"));
    if (nullptr != m_BoxCollision)
        m_BoxCollision->SetupAttachment(RootComponent);
}

void AEIInteractionPuzzle::BeginPlay()
{
    Super::BeginPlay();

    m_BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &AEIInteractionPuzzle::OnOverlapBegin);
}

void AEIInteractionPuzzle::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}