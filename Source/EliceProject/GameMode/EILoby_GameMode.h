// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "EILoby_GameMode.generated.h"

/**
 * 
 */
UCLASS()
class ELICEPROJECT_API AEILoby_GameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	AEILoby_GameMode();

public:
	virtual void PostInitializeComponents() override;

	//------- Login ------
	// -������ �����Ϸ��� �÷��̾ ó���� ��, ����Ǵ� �Լ�.
	virtual void PreLogin(const FString& Options, const FString& Address, const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage) override;

	// - �÷��̾ ������ ���� �Ϸ��ϰ� ���� ����Ǵ� �Լ�.
	virtual void PostLogin(APlayerController* NewPlayer) override;
	//----- Login END -----
};
