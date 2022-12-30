// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"

#include "Tickable.h"
#include "Engine/World.h"

#include "GameInstance/EILevelDefine.h"
#include "EIProcedureSystem.generated.h"

/**
 * 절차 시스템. OpenLevel, 접속 프로세스를 담당.
 */

class ULevel;
class UWorld;

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

public:
	FORCEINLINE EIOpenLevelType GetCurrentOpenLevelType() { return m_OpenLevelType; }

	void SetOpenLevelType(EIOpenLevelType InOpenLevelType);

	UFUNCTION(BlueprintCallable)
	void InitData(UObject* WorldContextObject);

	UFUNCTION(BlueprintCallable)
	void OnProcedureExecute(UObject* WorldContextObject, EIOpenLevelType InOpenLevelType);

	UFUNCTION(BlueprintCallable)
	void OnRestoreProcedure();

	UFUNCTION()
	void OnAllLevelLoad(ULevel* InLevel, UWorld* InWorld);

protected:
	void AddProcedure(EIProcedureType InProcedureType);

private:
	UPROPERTY(Transient)
	UObject* m_CachedContext = nullptr;

	UPROPERTY(Transient)
	TArray<UEIProcedure_Base*> m_ProcedureOrederList;

	UPROPERTY(Transient)
	UEIProcedure_Base* m_BeforeProcedure = nullptr;

	UPROPERTY(Transient)
	UEIProcedure_Base* m_CurrentProcedure = nullptr;
	
	EIOpenLevelType m_OpenLevelType = EIOpenLevelType::None;

	int32 m_ProcedureCount = 0;
	bool m_ProcedureStartTick = false;
};
