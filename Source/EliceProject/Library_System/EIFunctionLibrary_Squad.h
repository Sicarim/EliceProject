// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "EIFunctionLibrary_Squad.generated.h"

/**
 * Character, Squad를 생성하는 BlueprintFunctionLibrary
 */

class UEISquad;
class AEIGameCharacter;

UCLASS(BlueprintType, Blueprintable)
class ELICEPROJECT_API UEIFunctionLibrary_Squad : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (WorldContext = "WorldContextObject"))
	static UEISquad* Create_Squad(UObject* WorldContextObject, AActor* InOwner);

	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (WorldContext = "WorldContextObject"))
	static AEIGameCharacter* Create_GameCharacter(UObject* WorldContextObject, AActor* InOwner, int32 InCharacterID, FTransform InTransform);
};
