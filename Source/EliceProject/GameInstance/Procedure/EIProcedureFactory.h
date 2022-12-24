// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GameInstance/EILevelDefine.h"
#include "EIProcedureFactory.generated.h"

/**
 * Procedure »ý¼º.
 */

class UEIProcedure_Base;

UCLASS()
class ELICEPROJECT_API UEIProcedureFactory : public UObject
{
	GENERATED_BODY()
	
public:
	UEIProcedureFactory();

public:
	UFUNCTION(BlueprintCallable)
	static UEIProcedure_Base* CreateProcedure(UObject* WorldObjectContext);
};
