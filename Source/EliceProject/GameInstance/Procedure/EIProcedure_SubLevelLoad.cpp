// Fill out your copyright notice in the Description page of Project Settings.

#include "GameInstance/Procedure/EIProcedure_SubLevelLoad.h"

#include "Kismet/GameplayStatics.h"

UEIProcedure_SubLevelLoad::UEIProcedure_SubLevelLoad()
{

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

//* SubLevel Streaming은 여기서만 한다.*/
void UEIProcedure_SubLevelLoad::OnProcedureExecute(UObject* WorldContextObject)
{
	if (WorldContextObject == nullptr || WorldContextObject->IsValidLowLevel() == false)
	{
		EI_LOG(Warning, TEXT("[UEIProcedureSystem] WorldContextObject is nullptr"));
		return;
	}

	FEILevelData LevelData;
	GetLevelDataAt(m_OpenLevelType, LevelData);

	for (FSoftObjectPath ObjectPath : LevelData.sublevel_path_list)
	{
		FString LevelString = *ObjectPath.ToString();

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

		FName LevelName = FName(*ResultLevelString);
		FLatentActionInfo LatentInfo;
		UGameplayStatics::LoadStreamLevel(WorldContextObject, LevelName, true, false, LatentInfo);
	}
}

bool UEIProcedure_SubLevelLoad::IsProcedureComplete()
{
	return true;
}

void UEIProcedure_SubLevelLoad::OnRestoreProcedureData()
{

}