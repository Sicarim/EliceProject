// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "EICharacterData.generated.h"

/**
 * 공통적으로 쓰이는 CharacterData
 */

USTRUCT(BlueprintType)
struct FEICharacterData : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Character_id;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FSoftObjectPath bp_path;

public:
	FEICharacterData()
	{
		Character_id = 0;
		bp_path = nullptr;
	}
};