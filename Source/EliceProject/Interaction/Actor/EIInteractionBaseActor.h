// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interaction/Interface/EIInteraction.h"
#include "EIInteractionBaseActor.generated.h"

class UEIInteractionComponent;

/**
 * TO DO : �⺻�� �Ǵ� Interaction
 */

UCLASS(BlueprintType, Blueprintable)
class ELICEPROJECT_API AEIInteractionBaseActor : public AActor, public IEIInteraction
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEIInteractionBaseActor();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	
public:
	FORCEINLINE UEIInteractionComponent* GetInteractionComponent() { return m_InteractionComponent; }


protected:
	void InitInteraction();
	void IsEnableInteraction_Implimatation();

protected:
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "InteractionComponent", DisplayName = "InteractionComponent")
	UEIInteractionComponent* m_InteractionComponent;

};