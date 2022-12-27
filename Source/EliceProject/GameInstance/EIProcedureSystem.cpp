// Fill out your copyright notice in the Description page of Project Settings.

#include "GameInstance/EIProcedureSystem.h"

#include "EliceProject.h"

#include "GameInstance/Procedure/EIProcedureFactory.h"

#include "GameInstance/Procedure/EIProcedure_Base.h"
#include "GameInstance/Procedure/EIProcedure_PersistentLevel.h"
#include "GameInstance/Procedure/EIProcedure_SubLevelLoad.h"

UEIProcedureSystem::UEIProcedureSystem()
{
	InitData();
}

void UEIProcedureSystem::Tick(float DeltaTime)
{
	
}

bool UEIProcedureSystem::IsTickable() const
{
	return true;
}
	
TStatId UEIProcedureSystem::GetStatId() const
{
	return TStatId();
}

void UEIProcedureSystem::InitData()
{
	//Level이 열릴때 항상 지켜져야될 순서.
	AddProcedure(EIProcedureType::PersistentLevelLoad);
	AddProcedure(EIProcedureType::SubLevelLoad);
}

void UEIProcedureSystem::SetOpenLevelType(EIOpenLevelType InOpenLevelType)
{
	m_OpenLevelType = InOpenLevelType;
	for (UEIProcedure_Base* Procedure : m_ProcedureOrederList)
	{
		if (Procedure == nullptr || Procedure->IsValidLowLevel() == false)
			continue;

		Procedure->SetOpenLevelType(m_OpenLevelType);
	}
}

void UEIProcedureSystem::OnProcedureExecute(UObject* WorldContextObject, EIOpenLevelType InOpenLevelType)
{
	SetOpenLevelType(InOpenLevelType);

	for (UEIProcedure_Base* Procedure : m_ProcedureOrederList)
	{
		if (Procedure == nullptr || Procedure->IsValidLowLevel() == false)
			continue;

		Procedure->OnProcedureExecute(WorldContextObject);
	}
}

void UEIProcedureSystem::AddProcedure(EIProcedureType InProcedureType)
{
	UEIProcedure_Base* ProcedureBase = nullptr;
	ProcedureBase = UEIProcedureFactory::CreateProcedure(GetWorld(), InProcedureType);
	if (ProcedureBase == nullptr || ProcedureBase->IsValidLowLevel() == false)
	{
		EI_LOG(Warning, TEXT("[UEIProcedureSystem] ProcedureBase is nullptr"));
		return;
	}

	m_ProcedureOrederList.Add(ProcedureBase);
}
