// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "EISpawnBaseData.generated.h"

/**
 * 
 */
UCLASS()
class ELICEPROJECT_API UEISpawnBaseData : public UObject
{
	GENERATED_BODY()

public:
	UEISpawnBaseData();

public:
	virtual void InitSpawnData();
};