// Fill out your copyright notice in the Description page of Project Settings.

#include "Interaction/Actor/EIInteractionPuzzle.h"

#include "Net/UnrealNetwork.h"
#include "Components/BoxComponent.h"
#include "Components/SceneComponent.h"

#include "Character/Common/EIGameCharacter.h"

AEIInteractionPuzzle::AEIInteractionPuzzle()
{
    m_BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("PuzzleBoxCollision"));
    if (nullptr != m_BoxCollision)
        m_BoxCollision->SetupAttachment(RootComponent);
}

void AEIInteractionPuzzle::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    ////DOREPLIFETIME(AEIInteractionPuzzle, TestCharacter);
}

void AEIInteractionPuzzle::BeginPlay()
{
    Super::BeginPlay();

} 

void AEIInteractionPuzzle::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    
}

void AEIInteractionPuzzle::Interaction_BeginOverlap_Implementation(AActor* InActor)
{
    EI_LOG(Warning, TEXT("Puzzle Begin"));
}

void AEIInteractionPuzzle::Interaction_Execute_Implementation(AActor* InActor)
{
    EI_LOG(Warning, TEXT("Puzzle Execute"));
}

void AEIInteractionPuzzle::Interaction_EndOverlap_Implementation(AActor* InActor)
{
    EI_LOG(Warning, TEXT("Puzzle End"));
}