// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "EIPlayerController.generated.h"

class UCharacterMovementComponent;

/**
 * 
 */
UCLASS()
class ELICEPROJECT_API AEIPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	AEIPlayerController();

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
	virtual void PostInitializeComponents() override;
	virtual void OnPossess(APawn* InPawn) override;
	virtual void ProcessPlayerInput(const float DeltaTime, const bool bGamePaused) override;
	//-------------------------------------------------------------------//

public:
	void ForceMove(float DeltaTime);

	//Get
	//UCharacterMovementComponent* GetMovementComponent();

protected:
	

private:
	float m_ForceDeltaTime = 0.f;
};
