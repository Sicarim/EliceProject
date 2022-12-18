// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interaction/Actor/SpawnVolume/SpawnBehavior/EISpawnBaseBehavior.h"
#include "EISpawnMonsterBehavior.generated.h"

/**
 * 몬스터 스폰용 Behavior
 */

class UEISpawnBaseData;
class UEISpawnMonsterData;

UCLASS(EditInlineNew)
class ELICEPROJECT_API UEISpawnMonsterBehavior : public UEISpawnBaseBehavior
{
	GENERATED_BODY()
	
public:
	UEISpawnMonsterBehavior();

public:
	virtual void InitSpawnData(AEISpawnVolume* InSpawnVolume, UEISpawnBaseData* InSpawnData) override;
	virtual bool OnStartSpawn() override;

protected:
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, meta = (DisplayName = "Monster Spawn Data"))
	UEISpawnMonsterData* m_MonsterSpawnData;
};
