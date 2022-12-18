// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "EISpawnBaseBehavior.generated.h"

/**
 * SpawnVolume Behavior 부모 클래스
 */

class AEISpawnVolume;

class UEISpawnBaseData;

UCLASS()
class ELICEPROJECT_API UEISpawnBaseBehavior : public UObject
{
	GENERATED_BODY()
	
public:
	UEISpawnBaseBehavior();

public:
	virtual void InitSpawnData(AEISpawnVolume* InSpawnVolume, UEISpawnBaseData* InSpawnData);
	virtual bool OnStartSpawn() { return true; }

private:
	AEISpawnVolume* m_OwnerSpawnVolume = nullptr;
};
