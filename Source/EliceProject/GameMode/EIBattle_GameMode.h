// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "EIBattle_GameMode.generated.h"

/**
 * 
 */
UCLASS()
class ELICEPROJECT_API AEIBattle_GameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	AEIBattle_GameMode();

public:
	virtual void PostInitializeComponents() override;

	//------- Login ------
	// -������ �����Ϸ��� �÷��̾ ó���� ��, ����Ǵ� �Լ�.
	virtual void PreLogin(const FString& Options, const FString& Address, const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage) override;

	// - �÷��̾ ������ ���� �Ϸ��ϰ� ���� ����Ǵ� �Լ�.
	virtual void PostLogin(APlayerController* NewPlayer) override;
	//----- Login END -----
};
