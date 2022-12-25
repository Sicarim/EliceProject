// Fill out your copyright notice in the Description page of Project Settings.

#include "GameMode/EILoby_GameMode.h"

#include "Character/PC/EICharacter_InLoby.h"
#include "Character/Controller/EIPlayerController.h"
#include "GameState/EIGameState_InBattle.h"

AEILoby_GameMode::AEILoby_GameMode()
{
	DefaultPawnClass = AEICharacter_InLoby::StaticClass();
	PlayerControllerClass = AEIPlayerController::StaticClass();
	GameStateClass = AEIGameState_InBattle::StaticClass();
	//PlayerStateClass = AWarPlayerState::StaticClass();

	if (DefaultPawnClass == nullptr || DefaultPawnClass->IsValidLowLevel() == false)
	{
		UE_LOG(LogTemp, Error, TEXT("DefaultPawnClass is nullptr"));
		return;
	}

	if (PlayerControllerClass == nullptr || PlayerControllerClass->IsValidLowLevel() == false)
	{
		UE_LOG(LogTemp, Error, TEXT("PlayerControllerClass is nullptr"));
		return;
	}

	/*if (PlayerStateClass == nullptr)
	{
		ABLOG(Error, TEXT("Nullptr : PlayerStateClass"));
		return;
	}

	if (PlayerControllerClass == nullptr)
	{
		ABLOG(Error, TEXT("Error : PlayerControllerClass"));
		return;
	}

	if (HUDClass == nullptr)
	{
		ABLOG(Error, TEXT("Nullptr : HUDClass"));
		return;
	}*/
}

void AEILoby_GameMode::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	PlayerControllerClass = AEIPlayerController::StaticClass();
}

//------- Login ------
// -������ �����Ϸ��� �÷��̾ ó���� ��, ����Ǵ� �Լ�.
void AEILoby_GameMode::PreLogin(const FString& Options, const FString& Address, const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage)
{

}

// - �÷��̾ ������ ���� �Ϸ��ϰ� ���� ����Ǵ� �Լ�.
void AEILoby_GameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);
}
//----- Login END -----