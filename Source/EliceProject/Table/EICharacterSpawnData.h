// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine/DataTable.h"
#include "EICharacterSpawnData.generated.h"

/**
 * 스폰볼륨에서 사용하는 CharacterSpawnData
 */

USTRUCT(BlueprintType)
struct FEICharacterSpawnData : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 spawn_id;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 fomation_index;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 character_id_0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 slot_index_0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FSoftObjectPath character_ai_0;


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 character_id_1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 slot_index_1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FSoftObjectPath character_ai_1;


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 character_id_2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 slot_index_2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FSoftObjectPath character_ai_2;


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 character_id_3;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 slot_index_3;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FSoftObjectPath character_ai_3;


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 character_id_4;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 slot_index_4;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FSoftObjectPath character_ai_4;

public:
	FEICharacterSpawnData()
	{
		spawn_id = 0;
		fomation_index = 0;

		character_id_0 = 0;
		slot_index_0 = 0;
		character_ai_0 = nullptr;
		
		character_id_1 = 0;
		slot_index_1 = 0;
		character_ai_1 = nullptr;
		
		character_id_2 = 0;
		slot_index_2 = 0;
		character_ai_2 = nullptr;
		
		character_id_3 = 0;
		slot_index_3 = 0;
		character_ai_3 = nullptr;
		
		character_id_4 = 0;
		slot_index_4 = 0;
		character_ai_4 = nullptr;
	}
};