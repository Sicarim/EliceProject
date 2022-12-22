// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "EIMonsterData.generated.h"

/**
 * 공통적으로 쓰이는 MonsterData
 */

USTRUCT(BlueprintType)
struct FEIMonsterData : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Character_id;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 max_hp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FSoftObjectPath bp_path;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FSoftObjectPath character_ai;

public:
	FEIMonsterData()
	{
		Character_id = 0;
		max_hp = 1000;
		bp_path = nullptr;
		character_ai = nullptr;
	}
};