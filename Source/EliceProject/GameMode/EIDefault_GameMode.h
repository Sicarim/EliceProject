// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "EIDefault_GameMode.generated.h"

/**
 * 
 */
UCLASS()
class ELICEPROJECT_API AEIDefault_GameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AEIDefault_GameMode();

public:
	virtual void PostInitializeComponents() override;
	virtual void PostLogin(APlayerController* NewPlayer) override;
};
