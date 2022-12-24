// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "EITable.generated.h"

/**
 * 
 */

class UDataTable;

//Character
struct FEIMonsterData;

//Spawn
struct FEICharacterSpawnData;

//Formation
struct FEIFormationData;

//Level
struct FEILevelData;

UCLASS(BlueprintType, Blueprintable)
class ELICEPROJECT_API UEITable : public UObject
{
	GENERATED_BODY()
	
public:
	UEITable();

protected:
	void InitTableData();

public:
	//Character
	bool GetMonsterDataAt(int32 InDataId, FEIMonsterData& OutMonsterDataAt);

	bool GetSpawnDataAt(int32 InDataId, FEICharacterSpawnData& OutSpawnDataAt);

	//Spawn
	bool GetFormationDataAt(int32 InDataId, FEIFormationData& OutFormationDataAt);

	//Level
	bool GetLevelDataAt(int32 InDataId, FEILevelData& OutLevelDataAt);

protected:
	//Character
	UPROPERTY()
	UDataTable* m_MonsterData = nullptr;

	//Spawn
	UPROPERTY()
	UDataTable* m_CharacterSpawnData = nullptr;

	//Formation
	UPROPERTY()
	UDataTable* m_FormationData = nullptr;

	//Level
	UDataTable* m_LevelData = nullptr;
};
