// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "EIFunctionLibrary_System.generated.h"

/**
 * 
 */

class UEIGameInstance;

class UEILevelSystem;
class UEIGameUISystem;
class UEIProcedureSystem;
class UEIInteractionSystem;
class UEITable;

UCLASS(BlueprintType, Blueprintable)
class ELICEPROJECT_API UEIFunctionLibrary_System : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	UEIFunctionLibrary_System();

public:
	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (WorldContext = "WorldContextObject"))
	static UEIGameInstance* GetGameInstance(UObject* WorldContextObject);

	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (WorldContext = "WorldContextObject"))
	static UEIInteractionSystem* GetInteractionSystem(UObject* WorldContextObject);

	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (WorldContext = "WorldContextObject"))
	static UEIProcedureSystem* GetProcedureSystem(UObject* WorldContextObject);

	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (WorldContext = "WorldContextObject"))
	static UEIGameUISystem* GetUISystem(UObject* WorldContextObject);

	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (WorldContext = "WorldContextObject"))
	static UEILevelSystem* GetLevelSystem(UObject* WorldContextObject);

	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (WorldContext = "WorldContextObject"))
	static UEITable* GetTable(UObject* WorldContextObject);
};