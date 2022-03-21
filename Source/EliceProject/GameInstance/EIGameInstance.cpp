// Fill out your copyright notice in the Description page of Project Settings.

#include "GameInstance/EIGameInstance.h"

#include "Interaction/Interface/EIInteractionSystem.h"

UEIGameInstance::UEIGameInstance()
{

}

void UEIGameInstance::Init()
{
    CreateInstance();
    UE_LOG(LogTemp, Log, TEXT("NotifyActorBeginOverlap"));
}

void UEIGameInstance::StartGameInstance()
{

}

void UEIGameInstance::OnStart()
{

}

void UEIGameInstance::UEIGameInstance::Shutdown()
{

}

UEIInteractionSystem* UEIGameInstance::GetInteractionSystem()
{
    return GetInstance<UEIInteractionSystem>();
}

void UEIGameInstance::CreateInstance()
{
    AddInstance<UEIInteractionSystem>(NewObject<UEIInteractionSystem>(this));
}