// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GameInstance/EILevelDefine.h"
#include "EIProcedure_Base.generated.h"

/**
 * 
 */
UCLASS()
class ELICEPROJECT_API UEIProcedure_Base : public UObject
{
	GENERATED_BODY()
	
public:
	UEIProcedure_Base();

public:
	FORCEINLINE void SetOpenLevelType(EIOpenLevelType InOpenLevelType) { m_OpenLevelType = InOpenLevelType; }

	virtual void InitProcedure(UObject* WorldContextObject);
	virtual void OnProcedureExecute(UObject* WorldContextObject);

private:
	EIOpenLevelType m_OpenLevelType = EIOpenLevelType::None;
};
