// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
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

protected:
	virtual void InitProcedure(UObject* WorldContextObject);
	virtual void OnProcedureExecute(UObject* WorldContextObject);
};
