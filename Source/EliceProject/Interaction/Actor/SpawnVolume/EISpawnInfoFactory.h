// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "EISpawnInfoFactory.generated.h"

/**
 * SpawnBehavior, SpawnData »ý¼º.
 */

enum class EISpawnVolumeType : uint8;

class AEISpawnVolume;

class UEISpawnBaseData;
class UEISpawnBaseBehavior;

UCLASS(BlueprintType, Blueprintable)
class ELICEPROJECT_API UEISpawnInfoFactory : public UObject
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	static UEISpawnBaseData* CreateSpawnData(EISpawnVolumeType InSpawnVolumeType, AEISpawnVolume* InOwner);

	UFUNCTION(BlueprintCallable)
	static UEISpawnBaseBehavior* CreateSpawnBehavior(EISpawnVolumeType InSpawnVolumeType, AEISpawnVolume* InOwner, UEISpawnBaseData* InSpawnData);
};
