// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Interaction/Interface/EIInteractionEnum.h"
#include "EIInteractionSystem.generated.h"

/**
 * TO DO : Intance에 추가할 InteractionSystem
 */

DECLARE_DELEGATE_ThreeParams(FInteractionEvent, AActor*, EIInteractionObjectType, AActor*)
DECLARE_MULTICAST_DELEGATE_ThreeParams(FBeginOverlapEvent, AActor*, EIInteractionObjectType, AActor*)
DECLARE_MULTICAST_DELEGATE_ThreeParams(FExecuteEvent, AActor*, EIInteractionObjectType, AActor*)
DECLARE_MULTICAST_DELEGATE_ThreeParams(FEndOverlapEvent, AActor*, EIInteractionObjectType, AActor*)

UCLASS()
class ELICEPROJECT_API UEIInteractionSystem : public UObject
{
	GENERATED_BODY()
	
public:
	UEIInteractionSystem();

public:
	void Bind_BeginOverlap(EIInteractionObjectType InType, const FInteractionEvent& InDelegate);
	void Bind_Execute(EIInteractionObjectType InType, const FInteractionEvent& InDelegate);
	void Bind_EndOverlap(EIInteractionObjectType InType, const FInteractionEvent& InDelegate);

	void BroadCast_BeginOverlap(EIInteractionObjectType InType);
	void BroadCast_ExecuteOverlap();
	void BroadCast_EndOverlap();

protected:
	TMap<EIInteractionObjectType, FBeginOverlapEvent> m_BeginOverlapList;
	TMap<EIInteractionObjectType, FExecuteEvent> m_ExecuteList;
	TMap<EIInteractionObjectType, FEndOverlapEvent> m_EndOverlapList;
};
