// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TestInteractionActor.generated.h"

class UBoxComponent;
class AEIGameCharacter;
UCLASS()
class ELICEPROJECT_API ATestInteractionActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATestInteractionActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

protected:
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override; 
	virtual void NotifyActorEndOverlap(AActor* OtherActor) override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void TestMoveTrue();
	void TestMoveFalse();

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	UBoxComponent* m_BoxComponent;

	float m_DeltaTime = 0.f;
	bool m_Test = false;

	AEIGameCharacter* m_Character;
};
