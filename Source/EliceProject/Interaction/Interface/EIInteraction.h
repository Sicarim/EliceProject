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
	IEIInteraction();

public:
	//���ͷ��ǰ� ������ ����
	UFUNCTION(BlueprintNativeEvent)
	virtual bool IsOverlapInteraction() = 0;

	//���ͷ��ǰ� ��ȣ�ۿ� ���� ����
	UFUNCTION(BlueprintNativeEvent)
	virtual bool IsEnableInteraction() = 0;

	//���ͷ��� ���� ����
	UFUNCTION(BlueprintNativeEvent)
	virtual void UpdateInteractionState() = 0;

	//���ͷ��� ���� ����
	UFUNCTION(BlueprintNativeEvent)
	virtual void Interaction_BeginOverlap() = 0;

	//���ͷ��� ����
	UFUNCTION(BlueprintNativeEvent)
	virtual void Interaction_Execute() = 0;

	//���ͷ��� ���� ��������
	UFUNCTION(BlueprintNativeEvent)
	virtual void Interaction_EndOverlap() = 0;
};
