// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EIWidget_LobyButton.generated.h"

/**
 * Loby에 사용하는 버튼.
 */

class UButton;
class UEditableTextBox;

UCLASS()
class ELICEPROJECT_API UEIWidget_LobyButton : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UEIWidget_LobyButton(const FObjectInitializer& ObjectInitializer);
	
protected:
	virtual void NativeConstruct() override;

protected:
	UPROPERTY()
	UButton* m_MenuButton = nullptr;

	UPROPERTY()
	UEditableTextBox* m_MenuButtonText = nullptr;
};
