// Fill out your copyright notice in the Description page of Project Settings.

#include "Library_System/EIFunctionLibrary_System.h"

#include "Kismet/GameplayStatics.h"

#include "GameInstance/EILevelSystem.h"
#include "GameInstance/EIGameInstance.h"
#include "GameInstance/EIGameUISystem.h"
#include "GameInstance/EIProcedureSystem.h"
#include "Interaction/Interface/EIInteractionSystem.h"

UEIFunctionLibrary_System::UEIFunctionLibrary_System()
{

}

UEIGameInstance* UEIFunctionLibrary_System::GetGameInstance(UObject* WorldContextObject)
{
    if (nullptr == WorldContextObject)
        return nullptr;

    return Cast<UEIGameInstance>(UGameplayStatics::GetGameInstance(WorldContextObject));
}

UEIInteractionSystem* UEIFunctionLibrary_System::GetInteractionSystem(UObject* WorldContextObject)
{
    if (nullptr == WorldContextObject)
        return nullptr;

    UEIGameInstance* GameInstance = GetGameInstance(WorldContextObject);
    if (nullptr == GameInstance)
        return nullptr;
    
    return GameInstance->GetInstance<UEIInteractionSystem>();
}

UEIProcedureSystem* UEIFunctionLibrary_System::GetProcedureSystem(UObject* WorldContextObject)
{
    if (nullptr == WorldContextObject)
        return nullptr;

    UEIGameInstance* GameInstance = GetGameInstance(WorldContextObject);
    if (nullptr == GameInstance)
        return nullptr;

    return GameInstance->GetInstance<UEIProcedureSystem>();
}

UEIGameUISystem* UEIFunctionLibrary_System::GetUISystem(UObject* WorldContextObject)
{
    if (nullptr == WorldContextObject)
        return nullptr;

    UEIGameInstance* GameInstance = GetGameInstance(WorldContextObject);
    if (nullptr == GameInstance)
        return nullptr;

    return GameInstance->GetInstance<UEIGameUISystem>();
}

UEILevelSystem* UEIFunctionLibrary_System::GetLevelSystem(UObject* WorldContextObject)
{
    if (nullptr == WorldContextObject)
        return nullptr;

    UEIGameInstance* GameInstance = GetGameInstance(WorldContextObject);
    if (nullptr == GameInstance)
        return nullptr;

    return GameInstance->GetInstance<UEILevelSystem>();
}

UEITable* UEIFunctionLibrary_System::GetTable(UObject* WorldContextObject)
{
    if (nullptr == WorldContextObject)
        return nullptr;

    UEIGameInstance* GameInstance = GetGameInstance(WorldContextObject);
    if (nullptr == GameInstance)
        return nullptr;

    return GameInstance->GetInstance<UEITable>();
}