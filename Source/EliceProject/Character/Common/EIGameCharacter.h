// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Common/EICharacter.h"
#include "EIGameCharacter.generated.h"

/**
 * TO DO : 기본이 되는 GameCharacter
 */

class UEICharacterMovementComponent;
class UCharacterMovementComponent;
class AEIPlayerController;

UCLASS()
class ELICEPROJECT_API AEIGameCharacter : public AEICharacter
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
	//AEIPlayerController* m_PlayerController;
};
