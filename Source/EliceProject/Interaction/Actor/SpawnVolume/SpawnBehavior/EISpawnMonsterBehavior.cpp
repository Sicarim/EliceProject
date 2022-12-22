// Fill out your copyright notice in the Description page of Project Settings.

#include "Interaction/Actor/SpawnVolume/SpawnBehavior/EISpawnMonsterBehavior.h"

#include "Table/EIBattleDefine.h"

#include "Library_System/EIFunctionLibrary_Squad.h"

#include "Character/Common/EIGameCharacter.h"
#include "Interaction/Actor/SpawnVolume/EISpawnVolume.h"

#include "Character/Common/EISquad.h"

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
	if (m_MonsterSpawnData == nullptr || m_MonsterSpawnData->IsValidLowLevel() == false)
	{
		UE_LOG(LogTemp, Warning, TEXT("[UEISpawnMonsterBehavior] m_MonsterSpawnData is nullptr"));
		return false;
	}

	UEISquad* NewSquad = UEIFunctionLibrary_Squad::Create_Squad(m_OwnerSpawnVolume, m_OwnerSpawnVolume);
	if (NewSquad == nullptr || NewSquad->IsValidLowLevel() == false)
	{
		UE_LOG(LogTemp, Warning, TEXT("[UEISpawnMonsterBehavior] NewSquad is nullptr"));
		return false;
	}

	//캐릭터 생성.
	for (FEISpawnDataInfo& SpawnData : m_MonsterSpawnData->m_SpawnDataInfoList)
	{
		FTransform SpawnTransform = OnMakeSpawnTransform();
	}
	
	int32 Test = m_MonsterSpawnData->m_SpawnDataInfoList[0].m_SpawnDataID;

	UEIFunctionLibrary_Squad::Create_GameCharacter(m_OwnerSpawnVolume, m_OwnerSpawnVolume, Test, m_OwnerSpawnVolume->GetActorTransform());


	m_OwnerSpawnVolume->SetActorSquadList(NewSquad);

	return true;
}