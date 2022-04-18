// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "EIInteraction.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UEIInteraction : public UInterface
{
	GENERATED_BODY()
};

/**
 * TO DO : 상호작용을 위한 인터랙션 인터페이스
 */
class ELICEPROJECT_API IEIInteraction
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	IEIInteraction();

public:
	//인터랙션과 오버랩 여부
	UFUNCTION(BlueprintNativeEvent)
	virtual bool IsOverlapInteraction() = 0;

	//인터랙션과 상호작용 가능 여부
	UFUNCTION(BlueprintNativeEvent)
	virtual bool IsEnableInteraction() = 0;

	//인터랙션 상태 갱신
	UFUNCTION(BlueprintNativeEvent)
	virtual void UpdateInteractionState() = 0;

	//인터랙션 영역 진입
	UFUNCTION(BlueprintNativeEvent)
	virtual void Interaction_BeginOverlap() = 0;

	//인터랙션 실행
	UFUNCTION(BlueprintNativeEvent)
	virtual void Interaction_Execute() = 0;

	//인터랙션 영역 빠져나옴
	UFUNCTION(BlueprintNativeEvent)
	virtual void Interaction_EndOverlap() = 0;
};
