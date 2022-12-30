// Fill out your copyright notice in the Description page of Project Settings.

#include "GameInstance/Procedure/EIProcedure_Teleport.h"

#include "Kismet/GameplayStatics.h"

#include "Character/Common/EIGameCharacter.h"
#include "Components/CapsuleComponent.h"

UEIProcedure_Teleport::UEIProcedure_Teleport()
{
	m_ProcedureType = EIProcedureType::Teleport;
}

void UEIProcedure_Teleport::InitProcedure(UObject* WorldContextObject)
{
	if (WorldContextObject == nullptr || WorldContextObject->IsValidLowLevel() == false)
	{
		EI_LOG(Warning, TEXT("[UEIProcedureSystem] WorldContextObject is nullptr"));
		return;
	}

	Super::InitProcedure(WorldContextObject);
}

void UEIProcedure_Teleport::OnProcedureExecute(UObject* WorldContextObject)
{
	if (WorldContextObject == nullptr || WorldContextObject->IsValidLowLevel() == false)
	{
		EI_LOG(Warning, TEXT("[UEIProcedureSystem] WorldContextObject is nullptr"));
		return;
	}

	APlayerController* PC = UGameplayStatics::GetPlayerController(WorldContextObject, 0);
	if (PC == nullptr || PC->IsValidLowLevel() == false)
	{
		EI_LOG(Warning, TEXT("[UEIProcedureSystem] PC is nullptr"));
		return;
	}

	AEIGameCharacter* GameCharacter = Cast<AEIGameCharacter>(PC->GetPawn());
	if (PC == nullptr || PC->IsValidLowLevel() == false)
	{
		EI_LOG(Warning, TEXT("[UEIProcedureSystem] GameCharacter is nullptr"));
		return;
	}

	FEILevelData LevelData;
	GetLevelDataAt(m_OpenLevelType, LevelData);

	GameCharacter->SetActorNavLocation(LevelData.teleport_position);
	GameCharacter->SetActorRotation(LevelData.teleport_rotator);

	GameCharacter->GetCapsuleComponent()->SetCollisionProfileName(TEXT("Pawn"));
}

bool UEIProcedure_Teleport::IsProcedureComplete()
{
	return true;
}

void UEIProcedure_Teleport::OnRestoreProcedureData()
{

}