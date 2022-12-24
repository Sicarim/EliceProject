// Fill out your copyright notice in the Description page of Project Settings.

#include "GameInstance/Procedure/EIProcedureFactory.h"

#include "GameInstance/Procedure/EIProcedure_Base.h"

UEIProcedureFactory::UEIProcedureFactory()
{

}

UEIProcedure_Base* UEIProcedureFactory::CreateProcedure(UObject* WorldObjectContext)
{
	if (WorldObjectContext == nullptr || WorldObjectContext->IsValidLowLevel() == false)
	{
		UE_LOG(LogTemp, Warning, TEXT("[UEIProcedureFactory] WorldObjectContext is nullptr"));
		return nullptr;
	}

	UEIProcedure_Base* ProcedureBase = NewObject<UEIProcedure_Base>(WorldObjectContext);
	if (ProcedureBase == nullptr || ProcedureBase->IsValidLowLevel() == false)
	{
		UE_LOG(LogTemp, Warning, TEXT("[UEIProcedureFactory] ProcedureBase is nullptr"));
		return nullptr;
	}

	return ProcedureBase;
}