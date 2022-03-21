// Fill out your copyright notice in the Description page of Project Settings.

#include "Library_System/EIFunctionLibrary_System.h"

#include "Kismet/GameplayStatics.h"

#include "GameInstance/EIGameInstance.h"
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