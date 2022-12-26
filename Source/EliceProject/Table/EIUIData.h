// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GameInstance/EILevelDefine.h"
#include "EIUIData.generated.h"

/**
 * UI Define
 */

USTRUCT(BlueprintType)
struct FEIUIData : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EIWidgetType widget_type;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText memo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FSoftObjectPath ui_bp_path;

public:
	FEIUIData()
	{
		widget_type = EIWidgetType::None;
		memo = FText();
		ui_bp_path = nullptr;
	}
};