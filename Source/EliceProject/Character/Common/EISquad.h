// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Table/EIBattleDefine.h"
#include "EISquad.generated.h"

/**
 * 몬스터를 관리하는 Squad
 */

class AEIGameCharacter;

UCLASS(BlueprintType, Blueprintable)
class ELICEPROJECT_API UEISquad : public UObject
{
	GENERATED_BODY()
	
public:
	UEISquad();

public:
	FORCEINLINE TArray<FEISquadDataInfo> GetSquadCharacterList() { return m_SquadDataInfoList; };
	FORCEINLINE void SetSquadCharacterList(FEISquadDataInfo InData) { m_SquadDataInfoList.Add(InData); };

private:
	TArray<FEISquadDataInfo> m_SquadDataInfoList;
};
