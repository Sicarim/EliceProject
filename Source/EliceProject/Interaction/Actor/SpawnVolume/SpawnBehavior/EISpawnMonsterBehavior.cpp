// Fill out your copyright notice in the Description page of Project Settings.

#include "Interaction/Actor/SpawnVolume/SpawnBehavior/EISpawnMonsterBehavior.h"

#include "Interaction/Actor/SpawnVolume/SpawnData/EISpawnMonsterData.h"

UEISpawnMonsterBehavior::UEISpawnMonsterBehavior()
{

}

//* SpawnData 초기화 */
void UEISpawnMonsterBehavior::InitSpawnData(AEISpawnVolume* InSpawnVolume, UEISpawnBaseData* InSpawnData)
{
	Super::InitSpawnData(InSpawnVolume, InSpawnData);

	m_MonsterSpawnData = Cast<UEISpawnMonsterData>(InSpawnData);
}

//* 스폰 시작 */
bool UEISpawnMonsterBehavior::OnStartSpawn()
{
	bool IsSuccess = false;

	return IsSuccess;
}