// Fill out your copyright notice in the Description page of Project Settings.

#include "Table/EITable.h"

#include "Engine/DataTable.h"

//SpawnData
#include "Table/EICharacterSpawnData.h"

UEITable::UEITable()
{
	InitTableData();
}

void UEITable::InitTableData()
{
	//SpawnData
	FString CharacterSpawnDataPath = TEXT("/Game/Contents/Table/CharacterSpawnData.CharacterSpawnData");
	static ConstructorHelpers::FObjectFinder<UDataTable> SpawnData(*CharacterSpawnDataPath);
	m_CharacterSpawnData = SpawnData.Object;
}

//*  */
bool UEITable::GetSpawnDataAt(int32 InDataId, FEICharacterSpawnData& OutSpawnDataAt)
{
	if (m_CharacterSpawnData == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("[EITable] m_CharacterSpawnData is nullptr"));
		return false;
	}

	FEICharacterSpawnData* SpawnData = m_CharacterSpawnData->FindRow<FEICharacterSpawnData>(*FString::FromInt(InDataId), TEXT(""));
	if (m_CharacterSpawnData == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("[EITable] m_CharacterSpawnData FindRow Failed"));
		return false;
	}

	OutSpawnDataAt = *SpawnData;

	return true;
}