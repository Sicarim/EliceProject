// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "EIFormationData.generated.h"

/**
 * 스폰 혹은 위치를 지정할때 사용하는 FormationData
 */

USTRUCT(BlueprintType)
struct FEIFormationData : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 formation_id;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText memo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 interval;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool slot_0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool slot_1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool slot_2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool slot_3;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool slot_4;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool slot_5;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool slot_6;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool slot_7;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool slot_8;

public:
	FEIFormationData()
	{
		formation_id = 0;
		memo = FText();
		interval = 0;

		slot_0 = false;
		slot_1 = false;
		slot_2 = false;
		slot_3 = false;
		slot_4 = false;
		slot_5 = false;
		slot_6 = false;
		slot_7 = false;
		slot_8 = false;
	}
};