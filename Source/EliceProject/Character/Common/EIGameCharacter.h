// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/Common/EICharacter.h"
#include "Interaction/Interface/EIInteraction.h"
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
	// Get /
	//FORCEINLINE UCharacterMovementComponent* GetCharacterMovementComponent() { return GetMovementComponent(); }
	//FORCEINLINE AEIPlayerController* GetPlayerController() { return m_PlayerController; }

protected:
	void InitCharacter();

protected:
	//AEIPlayerController* m_PlayerController;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "InteractionComponent", DisplayName = "InteractionComponent")
	UEIInteractionComponent* m_InteractionComponent;
};
