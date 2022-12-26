// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/Common/EICharacter.h"
#include "Interaction/Interface/EIInteraction.h"
#include "EliceProject.h"
#include "EIGameCharacter.generated.h"

/**
 * TO DO : 기본이 되는 GameCharacter
 */

class AEIPlayerController;
class UEIInteractionComponent;
class UEICharacterMovementComponent;
class UCharacterMovementComponent;

UCLASS(BlueprintType, Blueprintable)
class ELICEPROJECT_API AEIGameCharacter : public AEICharacter, public IEIInteraction
{
	GENERATED_BODY()
	
public:
	AEIGameCharacter();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	//-------------------------------------------------------/

public:
	void SetActorNavLocation(FVector InLocation);

#pragma region Interaction
public:
	// >> Get
	FORCEINLINE UEIInteractionComponent* GetInteractionComponent() { return m_InteractionComponent; }
	// <<

	UFUNCTION(Server, Reliable)
	void Server_ExecuteInteractionEvent(AActor* InInteractionCharacter, AActor* InInteractionActor, EIInteractionEventType InEventType);

	UFUNCTION(Client, Reliable)
	void Client_ExecuteInteractionEvent(AActor* InInteractionCharacter, AActor* InInteractionActor, EIInteractionEventType InEventType);

	virtual void Interaction_CallEvent_Implementation(AActor* InActor, EIInteractionEventType InEventType) override;
	virtual void Interaction_EventProcess_Implementation(AActor* InActor, EIInteractionEventType InEventType) override;
	virtual bool IsEnableInteraction_Implementation(AActor* InActor, EIInteractionEventType InEventType) override;
	virtual void Interaction_EventCompliete_Implementation(AActor* InActor, EIInteractionEventType InEventType) override;

protected:
	virtual void Interaction_BeginOverlap_Implementation(AActor* InActor) override;
	virtual void Interaction_Execute_Implementation(AActor* InActor) override;
	virtual void Interaction_EndOverlap_Implementation(AActor* InActor) override;

	// Get /
	//FORCEINLINE UCharacterMovementComponent* GetCharacterMovementComponent() { return GetMovementComponent(); }
	//FORCEINLINE AEIPlayerController* GetPlayerController() { return m_PlayerController; }
#pragma endregion

protected:
	void InitCharacter();

protected:
	//AEIPlayerController* m_PlayerController;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "InteractionComponent", DisplayName = "InteractionComponent")
	UEIInteractionComponent* m_InteractionComponent;
};
