// Fill out your copyright notice in the Description page of Project Settings.

#include "Library_System/EIFunctionLibrary_Squad.h"

#include "Table/EITable.h"
#include "Table/EIMonsterData.h"

#include "Library_System/EIFunctionLibrary_System.h"

#include "Character/Common/EISquad.h"
#include "Character/Common/EIGameCharacter.h"

//* Squad 持失. */
UEISquad* UEIFunctionLibrary_Squad::Create_Squad(UObject* WorldContextObject, AActor* InOwner)
{
	if (WorldContextObject == nullptr || WorldContextObject->IsValidLowLevel() == false)
	{
		EI_LOG(Warning, TEXT("[UEIFunctionLibrary_Squad] InOwner is nullptr"));
		return nullptr;
	}

	if (InOwner == nullptr || InOwner->IsValidLowLevel() == false)
	{
		EI_LOG(Warning, TEXT("[UEIFunctionLibrary_Squad] InOwner is nullptr"));
		return nullptr;
	}

	UEISquad* Squad = nullptr;
	Squad = NewObject<UEISquad>(InOwner);
	if (Squad == nullptr || Squad->IsValidLowLevel() == false)
	{
		EI_LOG(Warning, TEXT("[UEIFunctionLibrary_Squad] Squad is nullptr"));
		return nullptr;
	}

	return Squad;
}

//* Character 持失. */
AEIGameCharacter* UEIFunctionLibrary_Squad::Create_GameCharacter(UObject* WorldContextObject, AActor* InOwner, int32 InCharacterID, FTransform InTransform)
{
	if (WorldContextObject == nullptr || WorldContextObject->IsValidLowLevel() == false)
	{
		EI_LOG(Warning, TEXT("[UEIFunctionLibrary_Squad] InOwner is nullptr"));
		return nullptr;
	}

	if (InOwner == nullptr || InOwner->IsValidLowLevel() == false)
	{
		EI_LOG(Warning, TEXT("[UEIFunctionLibrary_Squad] InOwner is nullptr"));
		return nullptr;
	}

	AEIGameCharacter* GameCharacter = nullptr;

	UEITable* Table = UEIFunctionLibrary_System::GetTable(WorldContextObject);
	if (Table == nullptr || Table->IsValidLowLevel() == false)
	{
		EI_LOG(Warning, TEXT("[UEIFunctionLibrary_Squad] Table is nullptr"));
		return nullptr;
	}

	FEIMonsterData MonsterData;
	if (Table->GetMonsterDataAt(InCharacterID, MonsterData) == false)
	{
		EI_LOG(Warning, TEXT("[UEIFunctionLibrary_Squad] GetMonsterDataAt is Failed"));
		return nullptr;
	}

	UObject* LoadObject = MonsterData.bp_path.TryLoad();
	if (LoadObject == nullptr || LoadObject->IsValidLowLevel() == false)
	{
		EI_LOG(Warning, TEXT("[UEIFunctionLibrary_Squad] LoadObject is nullptr"));
		return nullptr;
	}

	UClass* CharacterClass = Cast<UClass>(LoadObject);
	if (CharacterClass == nullptr || CharacterClass->IsValidLowLevel() == false)
	{
		EI_LOG(Warning, TEXT("[UEIFunctionLibrary_Squad] CharacterClass is nullptr"));
		return nullptr;
	}

	//Character Spawn
	FActorSpawnParameters SpawnParameter;
	SpawnParameter.Owner = InOwner;

	GameCharacter = WorldContextObject->GetWorld()->SpawnActor<AEIGameCharacter>(CharacterClass, SpawnParameter);
	if (GameCharacter == nullptr || GameCharacter->IsValidLowLevel() == false)
	{
		EI_LOG(Warning, TEXT("[UEIFunctionLibrary_Squad] GameCharacter is nullptr"));
		return nullptr;
	}

	if (GameCharacter->GetMesh() != nullptr && GameCharacter->GetMesh()->IsValidLowLevel() == true)
	{
		FVector Scale = GameCharacter->GetActorScale3D();
		FVector ResultScale = FVector(Scale.X * InTransform.GetScale3D().X, Scale.Y * InTransform.GetScale3D().Y, Scale.Z * InTransform.GetScale3D().Z);
		GameCharacter->SetActorScale3D(ResultScale);
	}
	GameCharacter->SetActorRotation(InTransform.GetRotation());
	GameCharacter->SetActorNavLocation(InTransform.GetLocation());

	return GameCharacter;
}