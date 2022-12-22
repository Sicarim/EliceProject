// Fill out your copyright notice in the Description page of Project Settings.

#include "Interaction/Actor/SpawnVolume/SpawnBehavior/EISpawnBaseBehavior.h"

#include "Table/EITable.h"
#include "Table/EIFormationData.h"
#include "Table/EICharacterSpawnData.h"

#include "Library_System/EIFunctionLibrary_Squad.h"
#include "Library_System/EIFunctionLibrary_System.h"
#include "Library_System/EIFunctionLibrary_FormationData.h"

#include "Interaction/Actor/SpawnVolume/EISpawnVolume.h"
#include "Interaction/Actor/SpawnVolume/SpawnData/EISpawnBaseData.h"

UEISpawnBaseBehavior::UEISpawnBaseBehavior()
{

}

//* SpawnData �ʱ�ȭ */
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

//* TableData�������� */
void UEISpawnBaseBehavior::GetTableDataAt(int32 InSpawnDataId, FEICharacterSpawnData& OutSpawnData, FEIFormationData& OutFormationData)
{
	UEITable* Table = UEIFunctionLibrary_System::GetTable(m_OwnerSpawnVolume);
	if (Table == nullptr || Table->IsValidLowLevel() == false)
	{
		UE_LOG(LogTemp, Warning, TEXT("[UEISpawnBaseBehavior] Table is nullptr"));
		return;
	}

	FEICharacterSpawnData CharacterSpawnData;
	if (Table->GetSpawnDataAt(InSpawnDataId, CharacterSpawnData) == false)
	{
		UE_LOG(LogTemp, Warning, TEXT("[UEISpawnBaseBehavior] FEICharacterSpawnData is Failed"));
		return;
	}

	OutSpawnData = CharacterSpawnData;

	FEIFormationData FormationData;
	/*if (Table->GetSpawnDataAt(InSpawnDataId, CharacterSpawnData) == false) -> �̰� �ٲ����(FormationData�д°� ��������....)
	{
		UE_LOG(LogTemp, Warning, TEXT("[UEISpawnBaseBehavior] FEICharacterSpawnData is Failed"));
		return;
	}*/

	OutFormationData = FormationData;
}

//* Spawn��ġ ����. */
FTransform UEISpawnBaseBehavior::OnMakeSpawnTransform()
{
	FTransform SpawnTransform;



	return SpawnTransform;
}

AEIGameCharacter* UEISpawnBaseBehavior::CreateSpawnActor()
{
	AEIGameCharacter* SpawnActor = nullptr;

	return SpawnActor;
}