// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interaction/Actor/SpawnVolume/SpawnData/EISpawnBaseData.h"
#include "EISpawnMonsterData.generated.h"

/**
 * 
 */
UCLASS()
class ELICEPROJECT_API UEISpawnMonsterData : public UEISpawnBaseData
{
	GENERATED_BODY()
	
public:
	UEISpawnMonsterData();

protected:
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, meta = (Category = "Spawn Monster Data", DisplayName = "Spawn Execute Type"))
	int32 m_test = 0;
};
