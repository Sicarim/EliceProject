// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/Main/EIWidget_LobyButton.h"

#include "Components/Button.h"
#include "Components/EditableTextBox.h"

UEIWidget_LobyButton::UEIWidget_LobyButton(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{

}

void UEIWidget_LobyButton::NativeConstruct()
{
	Super::NativeConstruct();

	m_MenuButton = Cast<UButton>(GetWidgetFromName(TEXT("MenuButton")));
	if (m_MenuButton == nullptr || m_MenuButton->IsValidLowLevel() == false)
	{
		EI_LOG(Warning, TEXT("[UEIWidget_LobyButton] m_MenuButton is nullptr"));
	}
	else
	{
		//m_MenuButton->OnClicked.AddDynamic(this, );
	}


	m_MenuButtonText = Cast<UEditableTextBox>(GetWidgetFromName(TEXT("LobyButtonText")));
	if (m_MenuButtonText == nullptr || m_MenuButtonText->IsValidLowLevel() == false)
		EI_LOG(Warning, TEXT("[UEIWidget_LobyButton] m_MenuButtonText is nullptr"));
}

