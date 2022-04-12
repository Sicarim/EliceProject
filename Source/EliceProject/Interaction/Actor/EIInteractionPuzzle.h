// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interaction/Actor/InteractionBaseActor.h"
#include "EIInteractionPuzzle.generated.h"

/**
 * To Do : 인터랙션 퍼즐
 */

class UBoxComponent;

UCLASS()
class ELICEPROJECT_API AEIInteractionPuzzle : public AInteractionBaseActor
{
	GENERATED_BODY()

public:
	AEIInteractionPuzzle();

protected:
	virtual void BeginPlay();
	virtual void Tick(float DeltaTime);

	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UBoxComponent* m_BoxCollision;

};
