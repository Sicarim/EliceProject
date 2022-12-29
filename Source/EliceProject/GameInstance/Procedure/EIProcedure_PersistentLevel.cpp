// Fill out your copyright notice in the Description page of Project Settings.

#include "GameInstance/Procedure/EIProcedure_PersistentLevel.h"

#include "Kismet/GameplayStatics.h"
#include "GameInstance/EIGameInstance.h"

UEIProcedure_PersistentLevel::UEIProcedure_PersistentLevel()
{

}

void UEIProcedure_PersistentLevel::InitProcedure(UObject* WorldContextObject)
{
	if (WorldContextObject == nullptr || WorldContextObject->IsValidLowLevel() == false)
	{
		EI_LOG(Warning, TEXT("[UEIProcedureSystem] WorldContextObject is nullptr"));
		return;
	}

	Super::InitProcedure(WorldContextObject); 
}

//* Open Level은 여기서만 한다.*/
void UEIProcedure_PersistentLevel::OnProcedureExecute(UObject* WorldContextObject)
{
	if (WorldContextObject == nullptr || WorldContextObject->IsValidLowLevel() == false)
	{
		EI_LOG(Warning, TEXT("[UEIProcedureSystem] WorldContextObject is nullptr"));
		return;
	}

	UGameInstance* GameInstance = UGameplayStatics::GetGameInstance(WorldContextObject);
	if (GameInstance == nullptr || GameInstance->IsValidLowLevel() == false)
	{
		EI_LOG(Warning, TEXT("[UEIProcedureSystem] GameInstance is nullptr"));
		return;
	}

	UEIGameInstance* EIGameInstance = Cast<UEIGameInstance>(GameInstance);
	if (EIGameInstance == nullptr || EIGameInstance->IsValidLowLevel() == false) 
	{
		EI_LOG(Warning, TEXT("[UEIProcedureSystem] EIGameInstance is nullptr"));
		return;
	}
	EIGameInstance->GetLevelChange_NewEvent().AddUObject(this, &UEIProcedure_PersistentLevel::OnLevelChange);

	FEILevelData LevelData;
	GetLevelDataAt(m_OpenLevelType, LevelData);

	FName LevelName = FName(*LevelData.persistant_level.ToString());
	UGameplayStatics::OpenLevel(WorldContextObject, LevelName);
}

bool UEIProcedure_PersistentLevel::IsProcedureComplete()
{
	return m_LevelChange;
}

void UEIProcedure_PersistentLevel::OnLevelChange()
{
	m_LevelChange = true;
}

void UEIProcedure_PersistentLevel::OnRestoreProcedureData()
{
	m_LevelChange = false;
}