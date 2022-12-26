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
class UEISquad;
class AEIGameCharacter;

class USphereComponent;
class USceneComponent;
class UEITargetComponent;

UENUM(BlueprintType)
enum class EISpawnExecuteType : uint8
{
	None,
	Start,
	Custom,
};

UCLASS(Blueprintable, Blueprintable, HideCategories = (EIInteractionBaseActor))
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

	//Get
	FORCEINLINE TArray<UEISquad*> GetActorSquadList() { return m_ActiveSquadList; }

	//Set
	FORCEINLINE void SetActorSquadList(UEISquad* InSquad) { m_ActiveSquadList.Add(InSquad); }

protected:
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, meta = (DisplayName = "Spawn Type"))
	EISpawnVolumeType m_SpawnType = EISpawnVolumeType::None;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, meta = (DisplayName = "Spawn Execute Type"))
	EISpawnExecuteType m_SpawnExecuteType = EISpawnExecuteType::None;

	UPROPERTY(Instanced, EditAnyWhere, BlueprintReadWrite, meta = (DisplayName = "Spawn Data"))
	UEISpawnBaseData* m_SpawnData = nullptr;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, meta = (Category = "SpawnVolume Setting"))
	USphereComponent* m_SphereCollision = nullptr;

	UPROPERTY()
	UEISpawnBaseBehavior* m_SpawnBehavior = nullptr;

	UPROPERTY(Transient)
	TArray<UEISquad*> m_ActiveSquadList;
	

#if WITH_EDITOR
public:
	virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;
	virtual bool CanEditChange(const FProperty* InProperty) const override;

	void CreateSpawnInfo();
	void UpdateSpawnDataInfo();
	void CreateTargetPoint();
	void ReleaseTargetPoint();

	void UpdateTargetPointPosition(UEITargetComponent* InTargetComponent);
#endif //WITH_EDITOR

#if WITH_EDITORONLY_DATA
	
#endif //WITH_EDITORONLY_DATA
};
