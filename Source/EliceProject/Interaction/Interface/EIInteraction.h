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
 * TO DO : ��ȣ�ۿ��� ���� ���ͷ��� �������̽�
 */
class ELICEPROJECT_API IEIInteraction
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	IEIInteraction() {}

public:
	//���ͷ��ǰ� ������ ����
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	bool IsOverlapInteraction();

	//���ͷ��ǰ� ��ȣ�ۿ� ���� ����
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	bool IsEnableInteraction();

	//���ͷ��� ���� ����
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void UpdateInteractionState();

	//���ͷ��� ���μ��� ����
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Interaction_Process();

	//���ͷ��� ���� ����
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Interaction_BeginOverlap();

	//���ͷ��� ����
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Interaction_Execute();

	//���ͷ��� ���� ��������
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Interaction_EndOverlap();
};
