// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameInstance/EIUIDefine.h"
#include "EIWidget_LobyButton.generated.h"

/**
 * Loby에 사용하는 버튼.
 */

class UButton;
class UEditableTextBox;

DECLARE_DELEGATE(FClickedButton_Event);

UCLASS()
class ELICEPROJECT_API UEIWidget_LobyButton : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UEIWidget_LobyButton(const FObjectInitializer& ObjectInitializer);
	
protected:
	virtual void NativeConstruct() override;

public:
	FORCEINLINE FClickedButton_Event& GetClicked_ButtonEvent() { return m_ClickedButton; }

	FORCEINLINE void SetButtonType(EILobyButtonType InButtonType) { m_ButtonType = InButtonType; }

protected:
	UFUNCTION()
	void ClickButtonClickEvent();

protected:
	UPROPERTY()
	UButton* m_MenuButton = nullptr;

	EILobyButtonType m_ButtonType = EILobyButtonType::None;

	FClickedButton_Event m_ClickedButton;
};
