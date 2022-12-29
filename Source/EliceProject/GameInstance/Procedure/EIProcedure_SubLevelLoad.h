// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameInstance/Procedure/EIProcedure_Base.h"
#include "EIProcedure_SubLevelLoad.generated.h"

/**
 * 
 */
UCLASS()
class ELICEPROJECT_API UEIProcedure_SubLevelLoad : public UEIProcedure_Base
{
	GENERATED_BODY()
	
public:
	UEIProcedure_SubLevelLoad();

public:
	virtual void InitProcedure(UObject* WorldContextObject) override;
	virtual void OnProcedureExecute(UObject* WorldContextObject) override;
	virtual bool IsProcedureComplete() override;
	virtual void OnRestoreProcedureData() override;
};
