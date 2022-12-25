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
	// -서버로 접근하려는 플레이어를 처리할 때, 실행되는 함수.
	virtual void PreLogin(const FString& Options, const FString& Address, const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage) override;

	// - 플레이어가 서버에 접근 완료하고 나서 실행되는 함수.
	virtual void PostLogin(APlayerController* NewPlayer) override;
	//----- Login END -----
};
