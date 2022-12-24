// Fill out your copyright notice in the Description page of Project Settings.

#include "GameInstance/EIProcedureSystem.h"

#include "GameInstance/Procedure/EIProcedureFactory.h"

#include "GameInstance/Procedure/EIProcedure_Base.h"
#include "GameInstance/Procedure/EIProcedure_PersistentLevel.h"
#include "GameInstance/Procedure/EIProcedure_SubLevelLoad.h"

UEIProcedureSystem::UEIProcedureSystem()
{

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

void UEIProcedureSystem::InitData(UObject* WorldContextObject)
{
	//Level이 열릴때 항상 지켜져야될 순서.
	AddProcedure(EIProcedureType::PersistentLevelLoad);
	AddProcedure(EIProcedureType::SubLevelLoad);
}

void UEIProcedureSystem::OnProcedureExecute(UObject* WorldContextObject)
{
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
	ProcedureBase = UEIProcedureFactory::CreateProcedure(GetWorld());

	switch (InProcedureType)
	{
	case EIProcedureType::PersistentLevelLoad:
	{
		UEIProcedure_PersistentLevel* Procedure_PersistentLevel = nullptr;
		Procedure_PersistentLevel = Cast<UEIProcedure_PersistentLevel>(Procedure_PersistentLevel);

		if (Procedure_PersistentLevel != nullptr && Procedure_PersistentLevel->IsValidLowLevel() == true)
			m_ProcedureOrederList.Add(Procedure_PersistentLevel);

		break;
	}
	case EIProcedureType::SubLevelLoad:
	{
		UEIProcedure_SubLevelLoad* Procedure_SubLevelLoad = nullptr;
		Procedure_SubLevelLoad = Cast<UEIProcedure_SubLevelLoad>(Procedure_SubLevelLoad);

		if (Procedure_SubLevelLoad != nullptr && Procedure_SubLevelLoad->IsValidLowLevel() == true)
			m_ProcedureOrederList.Add(Procedure_SubLevelLoad);

		break;
	}
	}
}
