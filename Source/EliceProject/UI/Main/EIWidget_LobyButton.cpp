// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/Main/EIWidget_LobyButton.h"

#include "EliceProject.h"
#include "Components/Button.h"
#include "Components/EditableTextBox.h"

UEIWidget_LobyButton::UEIWidget_LobyButton(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{

}

void UEIWidget_LobyButton::NativeConstruct()
{
	Super::NativeConstruct();

	m_MenuButton = Cast<UButton>(GetWidgetFromName(TEXT("LobyButton")));
	if (m_MenuButton != nullptr && m_MenuButton->IsValidLowLevel() == true)
		m_MenuButton->OnClicked.AddDynamic(this, &UEIWidget_LobyButton::ClickButtonClickEvent);
	else
		EI_LOG(Warning, TEXT("[UEIWidget_LobyButton] LobyButton is nullptr"));
}

void UEIWidget_LobyButton::ClickButtonClickEvent()
{
	if (m_ClickedButton.IsBound() == true)
		m_ClickedButton.Execute();
}

