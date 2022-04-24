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
	IEIInteraction() {}

public:
	//인터랙션과 오버랩 여부
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	bool IsOverlapInteraction();

	//인터랙션과 상호작용 가능 여부
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	bool IsEnableInteraction();

	//인터랙션 상태 갱신
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void UpdateInteractionState();

	//인터랙션 프로세스 실행
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Interaction_Process();

	//인터랙션 영역 진입
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Interaction_BeginOverlap();

	//인터랙션 실행
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Interaction_Execute();

	//인터랙션 영역 빠져나옴
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Interaction_EndOverlap();
};
