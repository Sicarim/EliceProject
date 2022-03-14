// Fill out your copyright notice in the Description page of Project Settings.

#include "TestInteractionActor.h"

#include "Components/BoxComponent.h"

#include "Character/Common/EIGameCharacter.h"

// Sets default values
ATestInteractionActor::ATestInteractionActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	m_BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("TestBoxComponent"));
	if (nullptr != m_BoxComponent)
		m_BoxComponent->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ATestInteractionActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATestInteractionActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (true == m_Test)
	{
		FVector MoveVector = m_Character->GetActorLocation();
		MoveVector.X += DeltaTime * 500.f;
		//m_Character->SetActorLocation(MoveVector);
	}
}

void ATestInteractionActor::NotifyActorBeginOverlap(AActor* OtherActor)
{ 
	UE_LOG(LogTemp, Log, TEXT("NotifyActorBeginOverlap"));

	TestMoveTrue();

	m_Character = Cast<AEIGameCharacter>(OtherActor);
	if (nullptr == m_Character || false == m_Character->IsValidLowLevel())
		return;
}

void ATestInteractionActor::NotifyActorEndOverlap(AActor* OtherActor) 
{ 
	UE_LOG(LogTemp, Log, TEXT("NotifyActorEndOverlap"));

	TestMoveFalse();
}

void ATestInteractionActor::TestMoveTrue()
{
	m_Test = true;
}

void ATestInteractionActor::TestMoveFalse()
{
	m_Test = false;
}