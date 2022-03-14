// Fill out your copyright notice in the Description page of Project Settings.

#include "../GameMode/EIDefault_GameMode.h"

//#include "../Character/PC/EIPlayer.h"
#include "Character/PC/EIPlayer.h"
#include "../Character/Controller/EIPlayerController.h"


AEIDefault_GameMode::AEIDefault_GameMode()
{
	PlayerControllerClass = AEIPlayerController::StaticClass();
	//PlayerStateClass = AWarPlayerState::StaticClass();

	if (nullptr == DefaultPawnClass)
	{
		UE_LOG(LogTemp, Error, TEXT("DefaultPawnClass is Nullptr"));
		return;
	}

	if (nullptr == PlayerControllerClass)
	{
		UE_LOG(LogTemp, Error, TEXT("PlayerControllerClass is Nullptr"));
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

void AEIDefault_GameMode::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	PlayerControllerClass = AEIPlayerController::StaticClass();
}


void AEIDefault_GameMode::PostLogin(APlayerController* NewPlayer)
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