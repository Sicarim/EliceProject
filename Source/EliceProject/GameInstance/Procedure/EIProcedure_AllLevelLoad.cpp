// Fill out your copyright notice in the Description page of Project Settings.

#include "GameInstance/Procedure/EIProcedure_AllLevelLoad.h"

UEIProcedure_AllLevelLoad::UEIProcedure_AllLevelLoad()
{
	m_ProcedureType = EIProcedureType::AllLevelLoad;
}

bool UEIProcedure_AllLevelLoad::IsProcedureComplete()
{
	return m_ProcedureComplete;
}

void UEIProcedure_AllLevelLoad::OnRestoreProcedureData()
{
	m_ProcedureComplete = false;
}

void UEIProcedure_AllLevelLoad::AllLevelLoadComplete()
{
	m_ProcedureComplete = true;
}