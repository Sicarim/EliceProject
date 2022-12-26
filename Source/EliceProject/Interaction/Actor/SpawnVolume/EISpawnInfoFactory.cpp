// Fill out your copyright notice in the Description page of Project Settings.

#include "Interaction/Actor/SpawnVolume/EISpawnInfoFactory.h"

#include "Table/EIBattleDefine.h"
#include "Interaction/Interface/EIInteractionEnum.h"

#include "Interaction/Actor/SpawnVolume/EISpawnVolume.h"

#include "Interaction/Actor/SpawnVolume/SpawnBehavior/EISpawnBaseBehavior.h"
#include "Interaction/Actor/SpawnVolume/SpawnBehavior/EISpawnMonsterBehavior.h"

#include "Interaction/Actor/SpawnVolume/SpawnData/EISpawnBaseData.h"
#include "Interaction/Actor/SpawnVolume/SpawnData/EISpawnMonsterData.h"

#include "Component/Spawn/EITargetComponent.h"

//* SpawnData 持失 */
UEISpawnBaseData* UEISpawnInfoFactory::CreateSpawnData(EISpawnVolumeType InSpawnVolumeType, AEISpawnVolume* InOwner)
{
    if (InOwner == nullptr || false == InOwner->IsValidLowLevel())
    {
        EI_LOG(Warning, TEXT("InOwner is nullptr"));
        return nullptr;
    }

    UEISpawnBaseData* SpawnData = nullptr;

    switch (InSpawnVolumeType)
    {
    case EISpawnVolumeType::Monster:
    {
        SpawnData = NewObject<UEISpawnMonsterData>(InOwner);
        if (SpawnData == nullptr || SpawnData->IsValidLowLevel() == false)
            return nullptr;

        break;
    }

    default:    break;
    }

    return SpawnData;
}

//* SpawnBehavior 持失 */
UEISpawnBaseBehavior* UEISpawnInfoFactory::CreateSpawnBehavior(EISpawnVolumeType InSpawnVolumeType, AEISpawnVolume* InOwner, UEISpawnBaseData* InSpawnData)
{
    if (InOwner == nullptr || false == InOwner->IsValidLowLevel())
    {
        EI_LOG(Warning, TEXT("InOwner is nullptr"));
        return nullptr;
    }

    UEISpawnBaseBehavior* SpawnBehavior = nullptr;

    switch (InSpawnVolumeType)
    {
    case EISpawnVolumeType::Monster:
    {
        SpawnBehavior = NewObject<UEISpawnMonsterBehavior>(InOwner);
        if (SpawnBehavior == nullptr || SpawnBehavior->IsValidLowLevel() == false)
            return nullptr;

        SpawnBehavior->InitSpawnData(InOwner, InSpawnData);
        break;
    }

    default:    break;
    }

    return SpawnBehavior;
}