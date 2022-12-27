// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/Main/Form/EIMain_Loby_Form.h"

#include "EliceProject.h"
#include "GameInstance/EILevelDefine.h"

#include "GameInstance/EIProcedureSystem.h"
#include "Library_System/EIFunctionLibrary_System.h"

#include "UI/Main/EIWidget_LobyButton.h"

UEIMain_Loby_Form::UEIMain_Loby_Form(const FObjectInitializer& ObjectInitializer)
    :Super(ObjectInitializer)
{

}

void UEIMain_Loby_Form::NativeConstruct()
{
	Super::NativeConstruct();

	m_MatchingButton = Cast<UEIWidget_LobyButton>(GetWidgetFromName(TEXT("Loby_Select_matching")));
	if (m_MatchingButton != nullptr && m_MatchingButton->IsValidLowLevel() == true)
	{
		m_MatchingButton->SetButtonType(EILobyButtonType::Matching);
		m_MatchingButton->GetClicked_ButtonEvent().BindUFunction(this, FName("Clicked_MatcingButton"));
	}
	else
		EI_LOG(Warning, TEXT("[UEIWidget_LobyButton] m_MatchingButton is nullptr"));
		
	m_BagButton = Cast<UEIWidget_LobyButton>(GetWidgetFromName(TEXT("Loby_Select_bag")));
	if (m_BagButton != nullptr && m_BagButton->IsValidLowLevel() == true)
	{
		m_BagButton->SetButtonType(EILobyButtonType::Bag);
		m_BagButton->GetClicked_ButtonEvent().BindUFunction(this, FName("Clicked_BagButton"));
	}
	else
		EI_LOG(Warning, TEXT("[UEIWidget_LobyButton] m_BagButton is nullptr"));
		
	m_ExitButton = Cast<UEIWidget_LobyButton>(GetWidgetFromName(TEXT("Loby_Select_exit")));
	if (m_ExitButton != nullptr && m_ExitButton->IsValidLowLevel() == true)
	{
		m_ExitButton->SetButtonType(EILobyButtonType::Exit);
		m_ExitButton->GetClicked_ButtonEvent().BindUFunction(this, FName("Clicked_ExitButton"));
	}
	else
		EI_LOG(Warning, TEXT("[UEIWidget_LobyButton] m_ExitButton is nullptr"));
}

void UEIMain_Loby_Form::Clicked_MatcingButton()
{
	UEIProcedureSystem* ProcedureSystem = UEIFunctionLibrary_System::GetProcedureSystem(this);
	if (ProcedureSystem == nullptr || ProcedureSystem->IsValidLowLevel() == false)
		return;

	ProcedureSystem->OnProcedureExecute(this, EIOpenLevelType::War_Place);
}

void UEIMain_Loby_Form::Clicked_BagButton()
{
	EI_LOG(Warning, TEXT(""));
}

void UEIMain_Loby_Form::Clicked_ExitButton()
{
	EI_LOG(Warning, TEXT(""));
}
