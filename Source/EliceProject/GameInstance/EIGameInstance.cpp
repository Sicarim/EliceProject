// Fill out your copyright notice in the Description page of Project Settings.

#include "GameInstance/EIGameInstance.h"

UEIGameInstance::UEIGameInstance()
{

}

void UEIGameInstance::Init()
{
    CreateInstance();
}

void UEIGameInstance::StartGameInstance()
{

}

void UEIGameInstance::OnStart()
{

}

void UEIGameInstance::UEIGameInstance::Shutdown()
{
    UE_LOG(LogTemp, Warning, TEXT("GameInstance Shut Down"));

    m_Instance.Empty();
}

void UEIGameInstance::CreateInstance()
{
    AddInstance<UEITable>(NewObject<UEITable>(this));
    AddInstance<UEILevelSystem>(NewObject<UEILevelSystem>(this));
    AddInstance<UEIGameUISystem>(NewObject<UEIGameUISystem>(this));

    AddInstance<UEIInteractionSystem>(NewObject<UEIInteractionSystem>(this));
    AddInstance<UEIProcedureSystem>(NewObject<UEIProcedureSystem>(this));
}