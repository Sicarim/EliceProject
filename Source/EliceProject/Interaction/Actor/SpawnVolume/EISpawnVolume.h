// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interaction/Actor/EIInteractionBaseActor.h"
#include "EISpawnVolume.generated.h"

/**
 * 여러 타입의 Actor를 스폰하는 스폰볼륨.
 */

enum class EISpawnVolumeType : uint8;

class UEISpawnBaseData;
class UEISpawnBaseBehavior;

UENUM(BlueprintType)
enum class EISpawnExecuteType : uint8
{
	None,
	Start,
	Custom,
};

UCLASS(Blueprintable, HideCategories = (EIInteractionBaseActor))
class ELICEPROJECT_API AEISpawnVolume : public AEIInteractionBaseActor
{
	GENERATED_BODY()

public:
	AEISpawnVolume();
	
protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

protected:
	bool InitSpawnData();

public:
	void StartSpawn();

protected:
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, meta = (DisplayName = "Spawn Type"))
	EISpawnVolumeType m_SpawnType = EISpawnVolumeType::None;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, meta = (DisplayName = "Spawn Execute Type"))
	EISpawnExecuteType m_SpawnExecuteType = EISpawnExecuteType::None;

	UPROPERTY(Instanced, EditAnyWhere, BlueprintReadWrite, meta = (DisplayName = "Spawn Data"))
	UEISpawnBaseData* m_SpawnData = nullptr;

	UPROPERTY()
	UEISpawnBaseBehavior* m_SpawnBehavior = nullptr;

#if WITH_EDITOR
	virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;
	virtual bool CanEditChange(const FProperty* InProperty) const override;

	void CreateSpawnInfo();
#endif //WITH_EDITOR

#if WITH_EDITORONLY_DATA
#endif //WITH_EDITORONLY_DATA
};
