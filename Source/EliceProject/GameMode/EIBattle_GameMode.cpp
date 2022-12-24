// Fill out your copyright notice in the Description page of Project Settings.

#include "GameMode/EIBattle_GameMode.h"

#include "Character/PC/EIPlayer.h"
#include "Character/Controller/EIPlayerController.h"
#include "EIGameState_InBattle.h"

AEIBattle_GameMode::AEIBattle_GameMode()
{
	DefaultPawnClass = AEIPlayer::StaticClass();
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

void AEIBattle_GameMode::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	PlayerControllerClass = AEIPlayerController::StaticClass();
}

//------- Login ------
	// -������ �����Ϸ��� �÷��̾ ó���� ��, ����Ǵ� �Լ�.
void AEIBattle_GameMode::PreLogin(const FString& Options, const FString& Address, const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage)
{

}

// - �÷��̾ ������ ���� �Ϸ��ϰ� ���� ����Ǵ� �Լ�.
void AEIBattle_GameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	/*auto WarPlayerState = Cast<AWarPlayerState>(NewPlayer->PlayerState);

	if (WarPlayerState == nullptr)
	{
		ABLOG(Error, TEXT("Nullptr : PlayerState"));
		return;
	}

	WarPlayerState->InitPlayerData();*/
}
//----- Login END -----


