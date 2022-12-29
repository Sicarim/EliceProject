// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "EliceProject.h"

#include "Table/EITable.h"
#include "Table/EILevelData.h"

#include "GameInstance/EILevelDefine.h"

#include "EIProcedure_Base.generated.h"

/**
 * 
 */

class UEITable;

UCLASS()
class ELICEPROJECT_API UEIProcedure_Base : public UObject
{
	GENERATED_BODY()
	
public:
	UEIProcedure_Base();

public:
	FORCEINLINE void SetOpenLevelType(EIOpenLevelType InOpenLevelType) { m_OpenLevelType = InOpenLevelType; }

	virtual void InitProcedure(UObject* WorldContextObject);
	virtual void OnProcedureExecute(UObject* WorldContextObject) {}
	virtual bool IsProcedureComplete();
	virtual void OnRestoreProcedureData() {}

public:
	void GetLevelDataAt(EIOpenLevelType InOpenLevelType, FEILevelData& OutLevelData);

protected:
	EIOpenLevelType m_OpenLevelType = EIOpenLevelType::None;

private:
	UPROPERTY()
	UEITable* m_Table = nullptr;
};
