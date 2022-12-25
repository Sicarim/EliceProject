// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Character/Common/EICharacterEnum.h"
#include "EICameraData.generated.h"

/**
 * CameraData
 */

USTRUCT(BlueprintType)
struct FEICameraData : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EICharacterCameraType camera_type;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText memo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float fov;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float arm_lengthTo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool busepawn_controlrotation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool binherit_pitch;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool binherit_roll;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool binherit_yaw;

public:
	FEICameraData()
	{
		camera_type = EICharacterCameraType::None;
		memo = FText();
		fov = 0.f;
		arm_lengthTo = 0.f;
		busepawn_controlrotation = true;
		binherit_pitch = true;
		binherit_roll = true;
		binherit_yaw = true;
	}
};