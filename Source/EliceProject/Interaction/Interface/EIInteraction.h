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
 * ��ȣ�ۿ��� ���� ���ͷ��� �������̽�
 */
class ELICEPROJECT_API IEIInteraction
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	IEIInteraction() {}

public:
	FORCEINLINE UEIInteractionComponent* GetInteractionComponent() { return nullptr; }

	//���ͷ��ǰ� ������ ����
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	bool IsOverlapInteraction(AActor* InActor);

	//���ͷ��ǰ� ��ȣ�ۿ� ���� ����
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	bool IsEnableInteraction(AActor* InActor, EIInteractionEventType InEventType);

	//���ͷ��� ���� ����
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void UpdateInteractionState(AActor* InActor);

	//���ͷ��� ȣ�� ����
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Interaction_CallEvent(AActor* InActor, EIInteractionEventType InEventType);

	//���ͷ��� ���μ��� ����
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Interaction_EventProcess(AActor* InActor, EIInteractionEventType InEventType);

	//���ͷ��� ���� ����
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Interaction_BeginOverlap(AActor* InActor);

	//���ͷ��� ����
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Interaction_Execute(AActor* InActor);

	//���ͷ��� ���� ��������
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Interaction_EndOverlap(AActor* InActor);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Interaction_LinkEvent(bool InActive);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Interaction_EventCompliete(AActor* InActor, EIInteractionEventType InEventType);
};
