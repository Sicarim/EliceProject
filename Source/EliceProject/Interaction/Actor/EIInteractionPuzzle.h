// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interaction/Actor/EIInteractionBaseActor.h"
#include "EIInteractionPuzzle.generated.h"

/**
 * To Do : 인터랙션 퍼즐
 */

class UBoxComponent;
class USceneComponent;

class AEIGameCharacter;

UCLASS()
class ELICEPROJECT_API AEIInteractionPuzzle : public AEIInteractionBaseActor
{
	GENERATED_BODY()

public:
	AEIInteractionPuzzle();

protected:
	virtual void BeginPlay();
	virtual void Tick(float DeltaTime);
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const;

protected:
	virtual void Interaction_BeginOverlap_Implementation(AActor* InActor);
	virtual void Interaction_Execute_Implementation(AActor* InActor);
	virtual void Interaction_EndOverlap_Implementation(AActor* InActor);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UBoxComponent* m_BoxCollision;

	int32 Test = 0;
};
