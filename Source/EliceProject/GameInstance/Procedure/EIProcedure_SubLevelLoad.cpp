// Fill out your copyright notice in the Description page of Project Settings.

#include "GameInstance/Procedure/EIProcedure_SubLevelLoad.h"

#include "Kismet/GameplayStatics.h"

UEIProcedure_SubLevelLoad::UEIProcedure_SubLevelLoad()
{
	m_ProcedureType = EIProcedureType::SubLevelLoad;
}

void UEIProcedure_SubLevelLoad::InitProcedure(UObject* WorldContextObject)
{
	if (WorldContextObject == nullptr || WorldContextObject->IsValidLowLevel() == false)
	{
		EI_LOG(Warning, TEXT("[UEIProcedureSystem] WorldContextObject is nullptr"));
		return;
	}

	Super::InitProcedure(WorldContextObject);
}

//* SubLevel Streaming�� ���⼭�� �Ѵ�.*/
void UEIProcedure_SubLevelLoad::OnProcedureExecute(UObject* WorldContextObject)
{
	if (WorldContextObject == nullptr || WorldContextObject->IsValidLowLevel() == false)
	{
		EI_LOG(Warning, TEXT("[UEIProcedureSystem] WorldContextObject is nullptr"));
		return;
	}

	FEILevelData LevelData;
	GetLevelDataAt(m_OpenLevelType, LevelData);

	// SubLevel Name �Ľ�
	FSoftObjectPath LevelObjectPath = LevelData.sublevel_path_list[m_StreamingCount];
	FString LevelString = *LevelObjectPath.ToString();

	TArray<FString> LevelStringArray;
	LevelString.ParseIntoArray(LevelStringArray, TEXT("."));

	FString ResultLevelString;
	if (LevelStringArray.IsValidIndex(LevelStringArray.Num() - 1) == true)
	{
		int32 StringLastNum = LevelStringArray.Num() - 1;
		ResultLevelString = LevelStringArray[StringLastNum];
	}
	else
	{
		EI_LOG(Error, TEXT("[UEIProcedure_SubLevelLoad] Level Find Failed"));
		return;
	}
	// << 

	// >> SubLevel �ε� üũ ���ε�
	UWorld* World = WorldContextObject->GetWorld();
	if (World == nullptr || World->IsValidLowLevel() == false)
		return;

	TArray<ULevelStreaming*> LevelStreamings = World->GetStreamingLevels();
	if (LevelStreamings.IsValidIndex(m_StreamingCount) == false)
		return;

	LevelStreamings[m_StreamingCount]->OnLevelLoaded.AddDynamic(this, &UEIProcedure_SubLevelLoad::OnLoadCompleteSubLevel);
	// << 

	// >> ���� ���� �ε�
	FName LevelName = FName(*ResultLevelString);
	FLatentActionInfo LatentInfo;
	UGameplayStatics::LoadStreamLevel(WorldContextObject, LevelName, true, true, LatentInfo);
	// <<

	++m_StreamingCount;
}

bool UEIProcedure_SubLevelLoad::IsProcedureComplete()
{
	return m_ProcedureComplete;
}

void UEIProcedure_SubLevelLoad::OnRestoreProcedureData()
{
	m_ProcedureComplete = false;
}

//* ���극�� �ε� �Ϸ� Ȯ�� */
void UEIProcedure_SubLevelLoad::OnLoadCompleteSubLevel()
{
	m_ProcedureComplete = true;
}

bool UEIProcedure_SubLevelLoad::OnIsSubLevelLoadComplete()
{
	return m_ProcedureComplete;
}
