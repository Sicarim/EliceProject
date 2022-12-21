// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "EITable.generated.h"

/**
 * 
 */

class UDataTable;

struct FEICharacterSpawnData;

UCLASS()
class ELICEPROJECT_API UEITable : public UObject
{
	GENERATED_BODY()
	
public:
	UEITable();

protected:
	void InitTableData();

public:
	bool GetSpawnDataAt(int32 InDataId, FEICharacterSpawnData& OutSpawnDataAt);

protected:
	UPROPERTY()
	UDataTable* m_CharacterSpawnData = nullptr;

};
