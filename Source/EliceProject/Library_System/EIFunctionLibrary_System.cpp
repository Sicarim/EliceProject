// Fill out your copyright notice in the Description page of Project Settings.

#include "Library_System/EIFunctionLibrary_System.h"

#include "Kismet/GameplayStatics.h"

#include "GameInstance/EIGameInstance.h"

UEIFunctionLibrary_System::UEIFunctionLibrary_System()
{

}

UEIGameInstance* UEIFunctionLibrary_System::GetGameInstance(UObject* WorldContextObject)
{
    if (nullptr == WorldContextObject)
        return nullptr;

    return Cast<UEIGameInstance>(UGameplayStatics::GetGameInstance(WorldContextObject));
}