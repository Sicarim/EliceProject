// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EIInteractionBaseActor.generated.h"

class UEIInteractionComponent;

/**
 * TO DO : 기본이 되는 Interaction
 */

UCLASS(BlueprintType, Blueprintable)
class ELICEPROJECT_API AEIInteractionBaseActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEIInteractionBaseActor();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

protected:
	void InitInteraction();

protected:
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "InteractionComponent", DisplayName = "InteractionComponent")
	UEIInteractionComponent* m_InteractionComponent;

};
