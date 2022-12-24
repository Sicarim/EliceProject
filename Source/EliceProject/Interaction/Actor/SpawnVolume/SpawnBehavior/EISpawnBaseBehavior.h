// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Table/EIBattleDefine.h"
#include "EISpawnBaseBehavior.generated.h"

/**
 * SpawnVolume Behavior 부모 클래스
 */

struct FEIFormationData;
struct FEICharacterSpawnData;

class UEISpawnBaseData;

class AEISpawnVolume;
class AEIGameCharacter;

UCLASS()
class ELICEPROJECT_API UEISpawnBaseBehavior : public UObject
{
	GENERATED_BODY()
	
public:
	UEISpawnBaseBehavior();

public:
	virtual void InitSpawnData(AEISpawnVolume* InSpawnVolume, UEISpawnBaseData* InSpawnData);
	virtual bool OnStartSpawn() { return true; }

protected:
	bool GetTableDataAt(int32 InSpawnDataId, FEICharacterSpawnData& OutSpawnData, FEIFormationData& OutFormationData);
	void GetSelectCreatureData(TArray<FEICreatureDataInfo>& OutCreateDataList, const FEICharacterSpawnData InSpawnData, const FEIFormationData InFormationData);
	TArray<int32> GetSlotIndex(const FEIFormationData InFormationData);

	FTransform OnMakeSpawnTransform(FVector InSpawnPosition, float Yaw, float InInterval, FEICreatureDataInfo& InCreatureData);
	AEIGameCharacter* CreateSpawnActor(FEICreatureDataInfo InCreatureData);
	
protected:
	AEISpawnVolume* m_OwnerSpawnVolume = nullptr;
};
