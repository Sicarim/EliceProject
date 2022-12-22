// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "EISpawnBaseBehavior.generated.h"

/**
 * SpawnVolume Behavior 부모 클래스
 */

struct FEICharacterSpawnData;
struct FEIFormationData;

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
	void GetTableDataAt(int32 InSpawnDataId, FEICharacterSpawnData& OutSpawnData, FEIFormationData& OutFormationData);
	FTransform OnMakeSpawnTransform();
	AEIGameCharacter* CreateSpawnActor();
	
protected:
	AEISpawnVolume* m_OwnerSpawnVolume = nullptr;
};
