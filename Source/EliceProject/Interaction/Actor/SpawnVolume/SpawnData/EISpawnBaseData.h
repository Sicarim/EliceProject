// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Table/EIBattleDefine.h"
#include "EISpawnBaseData.generated.h"

/**
 * 
 */

struct FEISpawnDataInfo;

UCLASS()
class ELICEPROJECT_API UEISpawnBaseData : public UObject
{
	GENERATED_BODY()

public:
	UEISpawnBaseData();

public:
	virtual void InitSpawnData();

public:
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, meta = (DisplayName = "Spawn Data Info"))
	TArray<FEISpawnDataInfo> m_SpawnDataInfoList;
};
