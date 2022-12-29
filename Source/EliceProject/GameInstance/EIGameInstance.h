// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "GameInstance/EILevelDefine.h"
#include "EIGameInstance.generated.h"

/**
 * 
 */

DECLARE_MULTICAST_DELEGATE(FOnLevelChange_NewWorld);
DECLARE_MULTICAST_DELEGATE(FOnLevelChange_OldWorld);

class UEITable;
class UEILevelSystem;
class UEIGameUISystem;
class UEIProcedureSystem;
class UEIInteractionSystem;

class UWorld;

UCLASS()
class ELICEPROJECT_API UEIGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UEIGameInstance(const FObjectInitializer& ObjectInitializer);

public:
	template <typename T>
	T* GetInstance()
	{
		const FName Key = FName(T::StaticClass()->GetName());
		if (m_Instance.Contains(Key) == false)
			return nullptr;

		return Cast<T>(m_Instance[Key]);
	}

	template <typename T = UObject>
	bool AddInstance(T* Inst)
	{
		const FName Key = FName(T::StaticClass()->GetName());
		if (nullptr != m_Instance.Find(Key))
			return false;

		m_Instance.Add(Key, Inst);
		return true;
	}

public:
	virtual void Init() override;
	virtual void StartGameInstance() override;
	virtual void OnStart() override;
	virtual void Shutdown() override;
	virtual void OnWorldChanged(UWorld* OldWorld, UWorld* NewWorld) override;

public:
	FORCEINLINE FOnLevelChange_NewWorld& GetLevelChange_NewEvent() { return m_OnLevelChange_NewEvent; }
	FORCEINLINE FOnLevelChange_OldWorld& GetLevelChange_OleEvent() { return m_OnLevelChange_OldEvent; }

	void Request_ExecuteProcedure(EIOpenLevelType InOpenLevelType);

protected:
	UEIInteractionSystem* GetInteractionSystem() { return GetInstance<UEIInteractionSystem>(); }
	UEIProcedureSystem* GetProcedureSystem() { return GetInstance<UEIProcedureSystem>(); }
	UEIGameUISystem* GetGameUISystem() { return GetInstance<UEIGameUISystem>(); }
	UEILevelSystem* GetLevelSystem() { return GetInstance<UEILevelSystem>(); }
	UEITable* GetTable() { return GetInstance<UEITable>(); }

	void CreateInstance();

protected:
	UPROPERTY(Transient)
	TMap<FName, UObject*> m_Instance;

	FOnLevelChange_NewWorld m_OnLevelChange_NewEvent;
	FOnLevelChange_OldWorld m_OnLevelChange_OldEvent;
};
