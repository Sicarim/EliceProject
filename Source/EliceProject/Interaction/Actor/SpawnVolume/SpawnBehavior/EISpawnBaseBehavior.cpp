// Fill out your copyright notice in the Description page of Project Settings.

#include "Interaction/Actor/SpawnVolume/SpawnBehavior/EISpawnBaseBehavior.h"

#include "Interaction/Actor/SpawnVolume/EISpawnVolume.h"
#include "Interaction/Actor/SpawnVolume/SpawnData/EISpawnBaseData.h"

UEISpawnBaseBehavior::UEISpawnBaseBehavior()
{

}

//* SpawnData ÃÊ±âÈ­ */
void UEISpawnBaseBehavior::InitSpawnData(AEISpawnVolume* InSpawnVolume, UEISpawnBaseData* InSpawnData)
{
	if (InSpawnVolume == nullptr || InSpawnVolume->IsValidLowLevel() == false)
	{
		UE_LOG(LogTemp, Warning, TEXT("InSpawnVolume is nullptr"));
		return;
	}

	if (InSpawnData == nullptr || InSpawnData->IsValidLowLevel() == false)
	{
		UE_LOG(LogTemp, Warning, TEXT("InSpawnData is nullptr"));
		return;
	}

	m_OwnerSpawnVolume = InSpawnVolume;
}