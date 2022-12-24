// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Tickable.h"
#include "GameInstance/EILevelDefine.h"
#include "EIProcedureSystem.generated.h"

/**
 * 절차 시스템. OpenLevel, 접속 프로세스를 담당.
 */

class UEIProcedure_Base;

UCLASS(Blueprintable, Blueprintable)
class ELICEPROJECT_API UEIProcedureSystem : public UObject, public FTickableGameObject
{
	GENERATED_BODY()
	
public:
	UEIProcedureSystem();

protected:
	virtual void Tick(float DeltaTime) override;
	virtual bool IsTickable() const override;
	virtual TStatId GetStatId() const override;

protected:
	UFUNCTION(BlueprintCallable)
	void InitData(UObject* WorldContextObject);

	UFUNCTION(BlueprintCallable)
	void OnProcedureExecute(UObject* WorldContextObject);

	void AddProcedure(EIProcedureType InProcedureType);

private:
	TArray<UEIProcedure_Base*> m_ProcedureOrederList;
};
