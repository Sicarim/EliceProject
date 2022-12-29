// Fill out your copyright notice in the Description page of Project Settings.

#include "GameInstance/EIGameInstance.h"

#include "EliceProject.h"

#include "Library_System/EIFunctionLibrary_System.h"

#include "Table/EITable.h"
#include "GameInstance/EILevelSystem.h"
#include "GameInstance/EIGameUISystem.h"
#include "GameInstance/EIProcedureSystem.h"
#include "Interaction/Interface/EIInteractionSystem.h"

UEIGameInstance::UEIGameInstance(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{

}

void UEIGameInstance::Init()
{
    Super::Init();

    CreateInstance();
}

void UEIGameInstance::StartGameInstance()
{
    Super::StartGameInstance();
}

void UEIGameInstance::OnStart()
{
    Super::OnStart();

    //Init Data
    UEIProcedureSystem* ProcedureSystem = GetProcedureSystem();
    if (ProcedureSystem == nullptr || ProcedureSystem->IsValidLowLevel() == false)
    {
        EI_LOG(Warning, TEXT("[EIGameInstance] ProcedureSystem is nullptr"));
        return;
    }

    ProcedureSystem->InitData(this);
}

void UEIGameInstance::UEIGameInstance::Shutdown()
{
    Super::Shutdown();

    EI_LOG(Warning, TEXT("[EIGameInstance] Shut Down"));

    m_Instance.Empty();
}

void UEIGameInstance::OnWorldChanged(UWorld* OldWorld, UWorld* NewWorld)
{
    Super::OnWorldChanged(OldWorld, NewWorld);

    // >> Old World
    if (OldWorld != nullptr && OldWorld->IsValidLowLevel() == true)
    {
        FString NameOldWorld = OldWorld->GetName();
        EI_LOG(Warning, TEXT("[EIGameInstance] NameOldWorld : %s"), *NameOldWorld);

        if (m_OnLevelChange_OldEvent.IsBound() == true)
            m_OnLevelChange_OldEvent.Broadcast();
    }
    // << 

    // >> New World
    if (NewWorld != nullptr && NewWorld->IsValidLowLevel() == true)
    {
        FString NameNewWorld = NewWorld->GetName();
        EI_LOG(Warning, TEXT("[EIGameInstance] NameNewWorld : %s"), *NameNewWorld);

        if (m_OnLevelChange_NewEvent.IsBound() == true)
            m_OnLevelChange_NewEvent.Broadcast();
    }
    // << 
}

void UEIGameInstance::Request_ExecuteProcedure(EIOpenLevelType InOpenLevelType)
{
    UEIProcedureSystem* ProcedureSystem = UEIFunctionLibrary_System::GetProcedureSystem(this);
    if (ProcedureSystem == nullptr || ProcedureSystem->IsValidLowLevel() == false)
        return;

    ProcedureSystem->OnProcedureExecute(this, EIOpenLevelType::War_Place);
}

void UEIGameInstance::CreateInstance()
{
    AddInstance<UEITable>(NewObject<UEITable>(this));
    AddInstance<UEILevelSystem>(NewObject<UEILevelSystem>(this));
    AddInstance<UEIGameUISystem>(NewObject<UEIGameUISystem>(this));

    AddInstance<UEIProcedureSystem>(NewObject<UEIProcedureSystem>(this));
    AddInstance<UEIInteractionSystem>(NewObject<UEIInteractionSystem>(this));
}