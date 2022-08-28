// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Interaction/Interface/EIInteractionEnum.h"
#include "Interaction/Component/EIInteractionComponent.h"
#include "EIInteraction.generated.h"

class UEIInteractionComponent;

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UEIInteraction : public UInterface
{
	GENERATED_BODY()
};

/**
 * 상호작용을 위한 인터랙션 인터페이스
 */
class ELICEPROJECT_API IEIInteraction
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	IEIInteraction() {}

public:
	FORCEINLINE UEIInteractionComponent* GetInteractionComponent() { return nullptr; }

	//인터랙션과 오버랩 여부
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	bool IsOverlapInteraction(AActor* InActor);

	//인터랙션과 상호작용 가능 여부
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	bool IsEnableInteraction(AActor* InActor, EIInteractionEventType InEventType);

	//인터랙션 상태 갱신
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void UpdateInteractionState(AActor* InActor);

	//인터랙션 호출 실행
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Interaction_CallEvent(AActor* InActor, EIInteractionEventType InEventType);

	//인터랙션 프로세스 실행
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Interaction_EventProcess(AActor* InActor, EIInteractionEventType InEventType);

	//인터랙션 영역 진입
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Interaction_BeginOverlap(AActor* InActor);

	//인터랙션 실행
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Interaction_Execute(AActor* InActor);

	//인터랙션 영역 빠져나옴
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Interaction_EndOverlap(AActor* InActor);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Interaction_LinkEvent(bool InActive);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Interaction_EventCompliete(AActor* InActor, EIInteractionEventType InEventType);
};
