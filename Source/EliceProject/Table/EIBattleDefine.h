// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "EIBattleDefine.generated.h"

class UEITargetComponent;

class AEIGameCharacter;

//* Squad Data Info */
USTRUCT(BlueprintType)
struct FEISquadDataInfo
{
	GENERATED_BODY()

public:
	int32 m_CharacterDataID;

	UPROPERTY()
	AEIGameCharacter* m_GameCharacter;

public:
	FEISquadDataInfo()
	{
		m_CharacterDataID = 0;
		m_GameCharacter = nullptr;
	}
};

//* SpawnData Info */
USTRUCT(BlueprintType)
struct FEISpawnDataInfo
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, meta = (DisplayName = "Spawn Data ID", ToolTip = "스폰 데이터 ID"))
	int32 m_SpawnDataID;

	FVector m_SpawnPosition;
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