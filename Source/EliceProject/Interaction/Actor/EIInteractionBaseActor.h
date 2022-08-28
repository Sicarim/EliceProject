// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interaction/Interface/EIInteraction.h"
#include "EIInteractionBaseActor.generated.h"

class UEIInteractionComponent;

/**
 * 기본이 되는 Interaction
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
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason);
	
public:
	// >> Get
	FORCEINLINE virtual UEIInteractionComponent* GetInteractionComponent() { return InteractionComponent; }
	// <<

	virtual void Interaction_CallEvent_Implementation(AActor* InActor, EIInteractionEventType InEventType);
	virtual void Interaction_EventProcess_Implementation(AActor* InActor, EIInteractionEventType InEventType);
	virtual bool IsEnableInteraction_Implementation(AActor* InActor, EIInteractionEventType InEventType);
	virtual void Interaction_EventCompliete_Implementation(AActor* InActor, EIInteractionEventType InEventType) override;

protected:
	UFUNCTION(Client, Reliable)
	void Client_ExecuteEvent(AActor* InInteractionCharacter, AActor* InInteractionActor, EIInteractionEventType InEventType);

	void InitInteraction();
	virtual void Interaction_BeginOverlap_Implementation(AActor* InActor) override;
	virtual void Interaction_Execute_Implementation(AActor* InActor) override;
	virtual void Interaction_EndOverlap_Implementation(AActor* InActor) override;
	virtual void Interaction_LinkEvent_Implementation(bool InActive) override;

protected:
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	UEIInteractionComponent* InteractionComponent;

};
