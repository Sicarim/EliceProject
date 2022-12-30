// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameInstance/Procedure/EIProcedure_Base.h"
#include "EIProcedure_AllLevelLoad.generated.h"

/**
 * 
 */
UCLASS()
class ELICEPROJECT_API UEIProcedure_AllLevelLoad : public UEIProcedure_Base
{
	GENERATED_BODY()
	
public:
	UEIProcedure_AllLevelLoad();

public:
	virtual bool IsProcedureComplete();
	virtual void OnRestoreProcedureData();

	void AllLevelLoadComplete();
};
