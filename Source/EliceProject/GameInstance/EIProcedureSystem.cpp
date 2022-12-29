// Fill out your copyright notice in the Description page of Project Settings.

#include "GameInstance/EIProcedureSystem.h"

#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"

#include "EliceProject.h"

#include "GameInstance/Procedure/EIProcedureFactory.h"

#include "GameInstance/Procedure/EIProcedure_Base.h"
#include "GameInstance/Procedure/EIProcedure_PersistentLevel.h"
#include "GameInstance/Procedure/EIProcedure_SubLevelLoad.h"

UEIProcedureSystem::UEIProcedureSystem()
{

}

void UEIProcedureSystem::Tick(float DeltaTime)
{
	if (m_ProcedureStartTick == false)
		return;
	if (m_CachedContext == nullptr || m_CachedContext->IsValidLowLevel() == false)
		return;
	if (m_CurrentProcedure == nullptr || m_CurrentProcedure->IsValidLowLevel() == false)
		return;

	if (m_CurrentProcedure->IsProcedureComplete() == true)
	{
		++m_ProcedureCount;
		if (m_ProcedureCount < m_ProcedureOrederList.Num())
		{
			m_BeforeProcedure = m_CurrentProcedure;
			m_CurrentProcedure = m_ProcedureOrederList[m_ProcedureCount];
			m_CurrentProcedure->OnProcedureExecute(m_CachedContext);
		}
		//Procedure절차가 모두 정상적으로 끝이 나면 다음 Procedure를 위해 초기화.
		else
		{
			OnRestoreProcedure();
		}
	}
}

bool UEIProcedureSystem::IsTickable() const
{
	return true;
}
	
TStatId UEIProcedureSystem::GetStatId() const
{
	return TStatId();
}

void UEIProcedureSystem::InitData(UObject* WorldContextObject)
{
	if (WorldContextObject == nullptr || WorldContextObject->IsValidLowLevel() == false)
	{
		EI_LOG(Warning, TEXT("[UEIProcedureSystem] WorldContextObject is nullptr"));
		return;
	}

	m_CachedContext = WorldContextObject;

	//Level이 열릴때 항상 지켜져야될 순서.
	AddProcedure(EIProcedureType::PersistentLevelLoad);
	AddProcedure(EIProcedureType::SubLevelLoad);
	AddProcedure(EIProcedureType::Teleport);
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
	
	if (m_ProcedureOrederList.IsValidIndex(m_ProcedureCount) == false)
	{
		EI_LOG(Error, TEXT("[UEIProcedureSystem] m_ProcedureOrederList IsValidIndex is false [m_ProcedureCount : %d]"), m_ProcedureCount);
		return;
	}
		
	m_CurrentProcedure = m_ProcedureOrederList[m_ProcedureCount];
	if (m_CurrentProcedure == nullptr || m_CurrentProcedure->IsValidLowLevel() == false)
	{
		EI_LOG(Error, TEXT("[UEIProcedureSystem] m_CurrentProcedure is nullptr"));
		return;
	}

	m_CurrentProcedure->OnProcedureExecute(WorldContextObject);
	m_ProcedureStartTick = true;
}

void UEIProcedureSystem::AddProcedure(EIProcedureType InProcedureType)
{
	if (m_CachedContext == nullptr || m_CachedContext->IsValidLowLevel() == false)
	{
		EI_LOG(Error, TEXT("[UEIProcedureSystem] m_CachedContext is nullptr"));
		return;
	}

	UEIProcedure_Base* ProcedureBase = nullptr;
	ProcedureBase = UEIProcedureFactory::CreateProcedure(m_CachedContext, InProcedureType);
	if (ProcedureBase == nullptr || ProcedureBase->IsValidLowLevel() == false)
	{
		EI_LOG(Warning, TEXT("[UEIProcedureSystem] ProcedureBase is nullptr"));
		return;
	}

	ProcedureBase->InitProcedure(m_CachedContext);
	m_ProcedureOrederList.Add(ProcedureBase);
}

void UEIProcedureSystem::OnRestoreProcedure()
{
	m_ProcedureStartTick = false;
	m_ProcedureCount = 0;

	for (UEIProcedure_Base* Procedure : m_ProcedureOrederList)
	{
		if (Procedure == nullptr || Procedure->IsValidLowLevel() == false)
			continue;

		Procedure->OnRestoreProcedureData();
	}
}