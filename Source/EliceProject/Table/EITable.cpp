// Fill out your copyright notice in the Description page of Project Settings.

#include "Table/EITable.h"

#include "Engine/DataTable.h"
#include "UObject/ConstructorHelpers.h"

//Monster Data
#include "Table/EIMonsterData.h"

//Spawn Data
#include "Table/EICharacterSpawnData.h"

//Formation Data
#include "Table/EIFormationData.h"

//Level Data
#include "Table/EILevelData.h"

UEITable::UEITable()
{
	InitTableData();
}

void UEITable::InitTableData()
{
	//MonsterData
	FString MonsterDataPath = TEXT("/Game/Contents/Table/MonsterData.MonsterData");
	static ConstructorHelpers::FObjectFinder<UDataTable> MonsterData(*MonsterDataPath);
	m_MonsterData = MonsterData.Object;

	//SpawnData
	FString CharacterSpawnDataPath = TEXT("/Game/Contents/Table/CharacterSpawnData.CharacterSpawnData");
	static ConstructorHelpers::FObjectFinder<UDataTable> SpawnData(*CharacterSpawnDataPath);
	m_CharacterSpawnData = SpawnData.Object;

	//Formation Data
	FString FormationDataPath = TEXT("/Game/Contents/Table/FormationData.FormationData");
	static ConstructorHelpers::FObjectFinder<UDataTable> FormationData(*FormationDataPath);
	m_FormationData = FormationData.Object;

	//Level Data
	FString LevelDataPath = TEXT("/Game/Contents/Table/LevelData.LevelData");
	static ConstructorHelpers::FObjectFinder<UDataTable> LeveData(*LevelDataPath);
	m_LevelData = LeveData.Object;
}

//* Monster SpawnData */
bool UEITable::GetMonsterDataAt(int32 InDataId, FEIMonsterData& OutMonsterDataAt)
{
	if (m_MonsterData == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("[EITable] m_MonsterData is nullptr"));
		return false;
	}

	FEIMonsterData* MonsterData = m_MonsterData->FindRow<FEIMonsterData>(*FString::FromInt(InDataId), TEXT(""));
	if (MonsterData == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("[EITable] MonsterData FindRow Failed"));
		return false;
	}

	OutMonsterDataAt = *MonsterData;

	return true;
}

//* Character SpawnData */
bool UEITable::GetSpawnDataAt(int32 InDataId, FEICharacterSpawnData& OutSpawnDataAt)
{
	if (m_CharacterSpawnData == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("[EITable] m_CharacterSpawnData is nullptr"));
		return false;
	}

	FEICharacterSpawnData* SpawnData = m_CharacterSpawnData->FindRow<FEICharacterSpawnData>(*FString::FromInt(InDataId), TEXT(""));
	if (SpawnData == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("[EITable] SpawnData FindRow Failed"));
		return false;
	}

	OutSpawnDataAt = *SpawnData;

	return true;
}

//* Formation Data */
bool UEITable::GetFormationDataAt(int32 InDataId, FEIFormationData& OutFormationDataAt)
{
	if (m_FormationData == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("[EITable] m_FormationData is nullptr"));
		return false;
	}

	FEIFormationData* FormationData = m_FormationData->FindRow<FEIFormationData>(*FString::FromInt(InDataId), TEXT(""));
	if (FormationData == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("[EITable] FormationData FindRow Failed"));
		return false;
	}

	OutFormationDataAt = *FormationData;

	return true;
}

bool UEITable::GetLevelDataAt(int32 InDataId, FEILevelData& OutLevelDataAt)
{
	if (m_LevelData == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("[EITable] m_LevelData is nullptr"));
		return false;
	}

	FEILevelData* LevelData = m_LevelData->FindRow<FEILevelData>(*FString::FromInt(InDataId), TEXT(""));
	if (LevelData == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("[EITable] LevelData FindRow Failed"));
		return false;
	}

	OutLevelDataAt = *LevelData;

	return true;
}