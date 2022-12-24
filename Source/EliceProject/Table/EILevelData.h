// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
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
	int32 Level_id;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText memo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<UWorld*> sublevel_list;

public:
	FEILevelData()
	{
		Level_id = 0;
		memo = FText();
	}
};