// Fill out your copyright notice in the Description page of Project Settings.

#include "GameInstance/Procedure/EIProcedureFactory.h"

#include "EliceProject.h"

#include "GameInstance/Procedure/EIProcedure_Base.h"
#include "GameInstance/Procedure/EIProcedure_PersistentLevel.h"
#include "GameInstance/Procedure/EIProcedure_SubLevelLoad.h"

UEIProcedureFactory::UEIProcedureFactory()
{

}

UEIProcedure_Base* UEIProcedureFactory::CreateProcedure(UObject* WorldObjectContext, EIProcedureType InProcedureType)
{
	if (WorldObjectContext == nullptr || WorldObjectContext->IsValidLowLevel() == false)
	{
		EI_LOG(Warning, TEXT("[UEIProcedureFactory] WorldObjectContext is nullptr"));
		return nullptr;
	}

	UEIProcedure_Base* ProcedureBase = nullptr;

	switch (InProcedureType)
	{
		case EIProcedureType::PersistentLevelLoad:
		{
			ProcedureBase = NewObject<UEIProcedure_PersistentLevel>(WorldObjectContext);
			break;
		}
		case EIProcedureType::SubLevelLoad:
		{
			ProcedureBase = NewObject<UEIProcedure_SubLevelLoad>(WorldObjectContext);
			break;
		}
	}

	if (ProcedureBase == nullptr || ProcedureBase->IsValidLowLevel() == false)
	{
		EI_LOG(Warning, TEXT("[UEIProcedureFactory] ProcedureBase is nullptr"));
		return nullptr;
	}

	return ProcedureBase;
}