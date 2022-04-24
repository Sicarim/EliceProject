// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interaction/Actor/EIInteractionBaseActor.h"
#include "EIInteractionPuzzle.generated.h"

/**
 * To Do : 인터랙션 퍼즐
 */

class UBoxComponent;

UCLASS()
class ELICEPROJECT_API AEIInteractionPuzzle : public AEIInteractionBaseActor
{
	GENERATED_BODY()

public:
	AEIInteractionPuzzle();

protected:
	virtual void BeginPlay();
	virtual void Tick(float DeltaTime);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UBoxComponent* m_BoxCollision;

};
