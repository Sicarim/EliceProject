// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractionBaseActor.generated.h"

/**
 * TO DO : 기본이 되는 Interaction
 */

class UEIInteractionComponent;

UCLASS(BlueprintType)
class ELICEPROJECT_API AInteractionBaseActor : public AActor
{
	GENERATED_BODY()
	
public:	
	AInteractionBaseActor();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

protected:

protected:
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "InteractionComponent", DisplayName = "InteractionComponent")
	UEIInteractionComponent* m_InteractionComponent;

};
