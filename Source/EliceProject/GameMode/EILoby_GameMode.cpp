// Fill out your copyright notice in the Description page of Project Settings.

#include "GameMode/EILoby_GameMode.h"

#include "Character/PC/EICharacter_InLoby.h"
#include "Character/Controller/EIPlayerController_InLoby.h"
#include "GameState/EIGameState_InLoby.h"

AEILoby_GameMode::AEILoby_GameMode()
{
	DefaultPawnClass = AEICharacter_InLoby::StaticClass();
	PlayerControllerClass = AEIPlayerController_InLoby::StaticClass();
	GameStateClass = AEIGameState_InLoby::StaticClass();

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

	PlayerControllerClass = AEIPlayerController_InLoby::StaticClass();
}

//------- Login ------
// -서버로 접근하려는 플레이어를 처리할 때, 실행되는 함수.
void AEILoby_GameMode::PreLogin(const FString& Options, const FString& Address, const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage)
{

}

// - 플레이어가 서버에 접근 완료하고 나서 실행되는 함수.
void AEILoby_GameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	if (NewPlayer == nullptr || NewPlayer->IsValidLowLevel() == false)
	{
		UE_LOG(LogTemp, Warning, TEXT("[AEILoby_GameMode] NewPlayer is nullptr"));
		return;
	}

	/*AEIGameState_InLoby* CharacterState = Cast<AEIGameState_InLoby>(NewPlayer->);
	if (CharacterState == nullptr || CharacterState->IsValidLowLevel() == false)
	{
		UE_LOG(LogTemp, Warning, TEXT("[AEILoby_GameMode] CharacterState is nullptr"));
		return;
	}*/

	//PlayerState->
}
//----- Login END -----