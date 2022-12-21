// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "EIBattleDefine.generated.h"

class UEITargetComponent;

USTRUCT(BlueprintType)
struct FEISpawnDataInfo
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, meta = (DisplayName = "Spawn Data ID", ToolTip = "스폰 데이터 ID"))
	int32 m_SpawnDataID;
	
	UPROPERTY()
	FVector m_SpawnPosition;

	UPROPERTY()
	float m_Yaw;

#if WITH_EDITOR
	UPROPERTY()
	UEITargetComponent* m_TargetPoint;
#endif //WITH_EDITOR

public:
	FEISpawnDataInfo()
	{
		m_SpawnDataID = 0;
		m_SpawnPosition = FVector::ZeroVector;
		m_Yaw = 0.f;

#if WITH_EDITOR
		m_TargetPoint = nullptr;
#endif //WITH_EDITOR
	}
};