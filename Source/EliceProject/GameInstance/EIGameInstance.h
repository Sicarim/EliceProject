// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "GameInstance/EIGameUISystem.h"
#include "GameInstance/EIProcedureSystem.h"
#include "GameInstance/EILevelSystem.h"
#include "Interaction/Interface/EIInteractionSystem.h"

#include "EIGameInstance.generated.h"

/**
 * 
 */

class UEILevelSystem;
class UEIGameUISystem;
class UEIProcedureSystem;
class UEIInteractionSystem;

UCLASS()
class ELICEPROJECT_API UEIGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UEIGameInstance();

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

protected:
	UEIInteractionSystem* GetInteractionSystem() { return GetInstance<UEIInteractionSystem>(); }
	UEIProcedureSystem* GetProcedureSystem() { return GetInstance<UEIProcedureSystem>(); }
	UEIGameUISystem* GetGameUISystem() { return GetInstance<UEIGameUISystem>(); }
	UEILevelSystem* GetLevelSystem() { return GetInstance<UEILevelSystem>(); }

	void CreateInstance();

protected:
	UPROPERTY(Transient)
	TMap<FName, UObject*> m_Instance;
};
