// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "EIFunctionLibrary_FormationData.generated.h"

/**
 * 
 */
UCLASS()
class ELICEPROJECT_API UEIFunctionLibrary_FormationData : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (WorldContext = "WorldContextObject"))
	static FVector GetFormationPosition(FVector InCenterPosition, int32 InInterval, int32 InSlotIdx);
};
