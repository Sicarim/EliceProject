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
	FText memo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 fomation_index;


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 character_id_0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Scale_0;


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 character_id_1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Scale_1;


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 character_id_2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Scale_2;


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 character_id_3;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Scale_3;


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 character_id_4;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Scale_4;

public:
	FEICharacterSpawnData()
	{
		spawn_id = 0;
		memo = FText();
		fomation_index = 0;

		character_id_0 = 0;
		Scale_0 = 1000;

		character_id_1 = 0;
		Scale_1 = 1000;
		
		character_id_2 = 0;
		Scale_2 = 1000;
		
		character_id_3 = 0;
		Scale_3 = 1000;
		
		character_id_4 = 0;
		Scale_4 = 1000;
	}
};