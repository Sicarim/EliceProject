// Fill out your copyright notice in the Description page of Project Settings.

#include "Interaction/Actor/SpawnVolume/SpawnBehavior/EISpawnBaseBehavior.h"

#include "NavigationSystem.h"

#include "Table/EITable.h"
#include "Table/EIFormationData.h"
#include "Table/EICharacterSpawnData.h"

#include "Kismet/KismetSystemLibrary.h"
#include "Library_System/EIFunctionLibrary_Squad.h"
#include "Library_System/EIFunctionLibrary_System.h"
#include "Library_System/EIFunctionLibrary_FormationData.h"

#include "Interaction/Actor/SpawnVolume/EISpawnVolume.h"
#include "Interaction/Actor/SpawnVolume/SpawnData/EISpawnBaseData.h"

#include "Character/Common/EIGameCharacter.h"

UEISpawnBaseBehavior::UEISpawnBaseBehavior()
{

}

//* SpawnData 초기화 */
void UEISpawnBaseBehavior::InitSpawnData(AEISpawnVolume* InSpawnVolume, UEISpawnBaseData* InSpawnData)
{
	if (InSpawnVolume == nullptr || InSpawnVolume->IsValidLowLevel() == false)
	{
		EI_LOG(Warning, TEXT("InSpawnVolume is nullptr"));
		return;
	}

	if (InSpawnData == nullptr || InSpawnData->IsValidLowLevel() == false)
	{
		EI_LOG(Warning, TEXT("InSpawnData is nullptr"));
		return;
	}

	m_OwnerSpawnVolume = InSpawnVolume;
}

//* TableData가져오기 */
bool UEISpawnBaseBehavior::GetTableDataAt(int32 InSpawnDataId, FEICharacterSpawnData& OutSpawnData, FEIFormationData& OutFormationData)
{
	UEITable* Table = UEIFunctionLibrary_System::GetTable(m_OwnerSpawnVolume);
	if (Table == nullptr || Table->IsValidLowLevel() == false)
	{
		EI_LOG(Warning, TEXT("[UEISpawnBaseBehavior] Table is nullptr"));
		return false;
	}

	FEICharacterSpawnData CharacterSpawnData;
	if (Table->GetSpawnDataAt(InSpawnDataId, CharacterSpawnData) == false)
	{
		EI_LOG(Warning, TEXT("[UEISpawnBaseBehavior] FEICharacterSpawnData is Failed"));
		return false;
	}

	OutSpawnData = CharacterSpawnData;

	FEIFormationData FormationData;
	if (Table->GetFormationDataAt(CharacterSpawnData.fomation_index, FormationData) == false)
	{
		EI_LOG(Warning, TEXT("[UEISpawnBaseBehavior] FEIFormationData is Failed"));
		return false;
	}

	OutFormationData = FormationData;

	return true;
}

//* 캐릭터 데이터 뽑아오기 */
void UEISpawnBaseBehavior::GetSelectCreatureData(TArray<FEICreatureDataInfo>& OutCreateDataList, const FEICharacterSpawnData InSpawnData, const FEIFormationData InFormationData)
{
	TArray<int32> SlotIndexList = GetSlotIndex(InFormationData);

	if (InSpawnData.character_id_0 != 0)
	{
		FEICreatureDataInfo CreatureData;

		CreatureData.m_SpawnDataID = InSpawnData.character_id_0;
		CreatureData.m_Scale = InSpawnData.Scale_0;

		if (SlotIndexList.IsValidIndex(0) == true)
			CreatureData.m_SlotIndex = SlotIndexList[0];

		OutCreateDataList.Add(CreatureData);
	}
	if (InSpawnData.character_id_1 != 0)
	{
		FEICreatureDataInfo CreatureData;

		CreatureData.m_SpawnDataID = InSpawnData.character_id_1;
		CreatureData.m_Scale = InSpawnData.Scale_1;

		if (SlotIndexList.IsValidIndex(1) == true)
			CreatureData.m_SlotIndex = SlotIndexList[1];

		OutCreateDataList.Add(CreatureData);
	}
	if (InSpawnData.character_id_2 != 0)
	{
		FEICreatureDataInfo CreatureData;

		CreatureData.m_SpawnDataID = InSpawnData.character_id_2;
		CreatureData.m_Scale = InSpawnData.Scale_2;

		if (SlotIndexList.IsValidIndex(2) == true)
			CreatureData.m_SlotIndex = SlotIndexList[2];

		OutCreateDataList.Add(CreatureData);
	}
	if (InSpawnData.character_id_3 != 0)
	{
		FEICreatureDataInfo CreatureData;

		CreatureData.m_SpawnDataID = InSpawnData.character_id_3;
		CreatureData.m_Scale = InSpawnData.Scale_3;

		if (SlotIndexList.IsValidIndex(3) == true)
			CreatureData.m_SlotIndex = SlotIndexList[3];

		OutCreateDataList.Add(CreatureData);
	}
	if (InSpawnData.character_id_4 != 0)
	{
		FEICreatureDataInfo CreatureData;

		CreatureData.m_SpawnDataID = InSpawnData.character_id_4;
		CreatureData.m_Scale = InSpawnData.Scale_4;

		if (SlotIndexList.IsValidIndex(4) == true)
			CreatureData.m_SlotIndex = SlotIndexList[4];

		OutCreateDataList.Add(CreatureData);
	}
}

//* Spawn위치 지정. */
FTransform UEISpawnBaseBehavior::OnMakeSpawnTransform(FVector InSpawnPosition, float Yaw, float InInterval, FEICreatureDataInfo& InCreatureData)
{
	FTransform SpawnTransform;
	FVector SpawnPosition = UEIFunctionLibrary_FormationData::GetFormationPosition(InSpawnPosition, InInterval, InCreatureData.m_SlotIndex);

	//TargetPoint위치를 Nav기준으로 스냅 시킨다.
	UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetNavigationSystem(m_OwnerSpawnVolume->GetWorld());
	if (NavSystem != nullptr && NavSystem->IsValidLowLevel() == true)
	{
		//Nav 검사
		FNavLocation NavLocation;
		if (NavSystem->ProjectPointToNavigation(SpawnPosition, NavLocation) == true)
			SpawnPosition = NavLocation.Location;
		else if (NavSystem->GetRandomPointInNavigableRadius(InSpawnPosition, InInterval, NavLocation) == true)
			SpawnPosition = NavLocation.Location;

		//Ray 검사.
		FVector StartPoint = SpawnPosition + (0.f, 0.f, 50.f);
		FVector EndPoint = SpawnPosition + (0.f, 0.f, -50.f);
		FHitResult HitResult;
		FVector HitPoint = FVector::ZeroVector;

		TArray<AActor*> IgnoreActors;
		bool Result = UKismetSystemLibrary::LineTraceSingleByProfile(m_OwnerSpawnVolume, StartPoint, EndPoint, TEXT("BlockAll"), false, IgnoreActors, EDrawDebugTrace::None, HitResult, true);
		if (Result == true)
		{
			HitPoint = HitResult.ImpactPoint;
			SpawnPosition = HitPoint;
		}
	}

	FRotator SpawnRotator = FRotator(0.f, Yaw, 0.f);
	FVector SpawnScale = FVector(InCreatureData.m_Scale * 0.001f, InCreatureData.m_Scale * 0.001f, InCreatureData.m_Scale * 0.001f);
	SpawnTransform = FTransform(SpawnRotator, SpawnPosition, SpawnScale);
	InCreatureData.m_SpawnTransform = SpawnTransform;

	return SpawnTransform;
}

AEIGameCharacter* UEISpawnBaseBehavior::CreateSpawnActor(FEICreatureDataInfo InCreatureData)
{
	AEIGameCharacter* SpawnActor = nullptr;
	SpawnActor = UEIFunctionLibrary_Squad::Create_GameCharacter(m_OwnerSpawnVolume, m_OwnerSpawnVolume, InCreatureData.m_SpawnDataID, InCreatureData.m_SpawnTransform);
	if (SpawnActor == nullptr || SpawnActor->IsValidLowLevel() == false)
	{
		EI_LOG(Warning, TEXT("[UEIFunctionLibrary_Squad] SpawnActor is nullptr"));
		return nullptr;
	}

	return SpawnActor;
}

TArray<int32> UEISpawnBaseBehavior::GetSlotIndex(const FEIFormationData InFormationData)
{
	TArray<int32> SlotIndexList;

	if (InFormationData.slot_0 == true)
		SlotIndexList.Add(0);
	if (InFormationData.slot_1 == true)
		SlotIndexList.Add(1);
	if (InFormationData.slot_2 == true)
		SlotIndexList.Add(2);
	if (InFormationData.slot_3 == true)
		SlotIndexList.Add(3);
	if (InFormationData.slot_4 == true)
		SlotIndexList.Add(4);
	if (InFormationData.slot_5 == true)
		SlotIndexList.Add(5);
	if (InFormationData.slot_6 == true)
		SlotIndexList.Add(6);
	if (InFormationData.slot_7 == true)
		SlotIndexList.Add(7);
	if (InFormationData.slot_8 == true)
		SlotIndexList.Add(8);

	return SlotIndexList;
}