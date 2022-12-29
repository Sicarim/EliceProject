// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GameInstance/EILevelDefine.h"
#include "EILevelData.generated.h"

/**
 * Level 전환에 사용되는 LevelData
 */

class UWorld;

USTRUCT(BlueprintType)
struct FEILevelData : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EIOpenLevelType openlevel_type;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText memo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FSoftObjectPath persistant_level;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector teleport_position;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FRotator teleport_rotator;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FSoftObjectPath> sublevel_path_list;

public:
	FEILevelData()
	{
		openlevel_type = EIOpenLevelType::None;
		memo = FText();
		persistant_level = nullptr;
		teleport_position = FVector::ZeroVector;
		teleport_rotator = FRotator::ZeroRotator;
	}
};