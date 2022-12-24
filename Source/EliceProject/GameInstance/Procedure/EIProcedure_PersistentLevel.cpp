// Fill out your copyright notice in the Description page of Project Settings.

#include "GameInstance/Procedure/EIProcedure_PersistentLevel.h"

#include "Kismet/GameplayStatics.h"

#include "Table/EITable.h"
#include "Table/EILevelData.h"

#include "Library_System/EIFunctionLibrary_System.h"

UEIProcedure_PersistentLevel::UEIProcedure_PersistentLevel()
{

}

void UEIProcedure_PersistentLevel::InitProcedure(UObject* WorldContextObject)
{
	if (WorldContextObject == nullptr || WorldContextObject->IsValidLowLevel() == false)
	{
		UE_LOG(LogTemp, Warning, TEXT("[UEIProcedureSystem] WorldContextObject is nullptr"));
		return;
	}

	UEITable* Table = UEIFunctionLibrary_System::GetTable(WorldContextObject);
	if (Table == nullptr || Table->IsValidLowLevel() == false)
	{
		UE_LOG(LogTemp, Warning, TEXT("[UEIProcedureSystem] Table is nullptr"));
		return;
	}

	//FEILevelData LevelData;
}

//* Open Level은 여기서만 한다.*/
void UEIProcedure_PersistentLevel::OnProcedureExecute(UObject* WorldContextObject)
{
	if (WorldContextObject == nullptr || WorldContextObject->IsValidLowLevel() == false)
	{
		UE_LOG(LogTemp, Warning, TEXT("[UEIProcedureSystem] WorldContextObject is nullptr"));
		return;
	}

	//UGameplayStatics::OpenLevel(WorldContextObject, );
}