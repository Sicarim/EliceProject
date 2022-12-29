// Fill out your copyright notice in the Description page of Project Settings.

#include "GameInstance/Procedure/EIProcedure_Base.h"

#include "Library_System/EIFunctionLibrary_System.h"

UEIProcedure_Base::UEIProcedure_Base()
{

}

void UEIProcedure_Base::InitProcedure(UObject* WorldContextObject)
{
	if (WorldContextObject == nullptr || WorldContextObject->IsValidLowLevel() == false)
	{
		EI_LOG(Warning, TEXT("[UEIProcedureSystem] WorldContextObject is nullptr"));
		return;
	}

	m_Table = UEIFunctionLibrary_System::GetTable(WorldContextObject);
	if (m_Table == nullptr || m_Table->IsValidLowLevel() == false)
	{
		EI_LOG(Warning, TEXT("[UEIProcedureSystem] Table is nullptr"));
		return;
	}
}

void UEIProcedure_Base::GetLevelDataAt(EIOpenLevelType InOpenLevelType, FEILevelData& OutLevelData)
{
	if (m_Table == nullptr || m_Table->IsValidLowLevel() == false)
	{
		EI_LOG(Warning, TEXT("[UEIProcedureSystem] Table is nullptr"));
		return;
	}

	m_Table->GetLevelDataAt((int)InOpenLevelType, OutLevelData);
}

bool UEIProcedure_Base::IsProcedureComplete()
{
	return false;
}