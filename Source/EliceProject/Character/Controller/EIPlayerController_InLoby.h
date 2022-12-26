// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "EIPlayerController_InLoby.generated.h"

/**
 * 로비용 컨트롤러.
 */

class UEIMain_Loby_Form;

UCLASS(Blueprintable, Blueprintable)
class ELICEPROJECT_API AEIPlayerController_InLoby : public APlayerController
{
	GENERATED_BODY()
	
public:
	AEIPlayerController_InLoby();

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
	virtual void PostInitializeComponents() override;
	virtual void OnPossess(APawn* InPawn) override;
	virtual void ProcessPlayerInput(const float DeltaTime, const bool bGamePaused) override;

private:
	UPROPERTY()
	UEIMain_Loby_Form* m_MainLobyWidget = nullptr;
};
