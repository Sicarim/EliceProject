// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/Main/Form/EIMain_Loby_Form.h"

#include "UI/Main/EIWidget_LobyButton.h"

UEIMain_Loby_Form::UEIMain_Loby_Form(const FObjectInitializer& ObjectInitializer)
    :Super(ObjectInitializer)
{

}

void UEIMain_Loby_Form::NativeConstruct()
{
	Super::NativeConstruct();

	//현재 L버튼은 두개, R버튼은 3개로 고정. 따로 규칙이 없어 하드코딩으로 진행.

	//----- L 버튼 -----
	UEIWidget_LobyButton* LobyButton_L_0 = Cast<UEIWidget_LobyButton>(GetWidgetFromName(TEXT("Loby_Select_button_L_0")));
	if (LobyButton_L_0 != nullptr && LobyButton_L_0->IsValidLowLevel() == true)
		m_MenuButtonList_L.Add(LobyButton_L_0);
	else
		EI_LOG(Warning, TEXT("[UEIWidget_LobyButton] LobyButton_L_0 is nullptr"));

	UEIWidget_LobyButton* LobyButton_L_1 = Cast<UEIWidget_LobyButton>(GetWidgetFromName(TEXT("Loby_Select_button_L_1")));
	if (LobyButton_L_1 != nullptr && LobyButton_L_1->IsValidLowLevel() == true)
		m_MenuButtonList_L.Add(LobyButton_L_1);
	else
		EI_LOG(Warning, TEXT("[UEIWidget_LobyButton] LobyButton_L_1 is nullptr"));
	//---- L 버튼 END----
		
	//----- R 버튼 -----
	UEIWidget_LobyButton* LobyButton_R_0 = Cast<UEIWidget_LobyButton>(GetWidgetFromName(TEXT("Loby_Select_button_R_0")));
	if (LobyButton_R_0 != nullptr && LobyButton_R_0->IsValidLowLevel() == true)
		m_MenuButtonList_R.Add(LobyButton_R_0);
	else
		EI_LOG(Warning, TEXT("[UEIWidget_LobyButton] LobyButton_R_0 is nullptr"));

	UEIWidget_LobyButton* LobyButton_R_1 = Cast<UEIWidget_LobyButton>(GetWidgetFromName(TEXT("Loby_Select_button_R_1")));
	if (LobyButton_R_1 != nullptr && LobyButton_R_1->IsValidLowLevel() == true)
		m_MenuButtonList_R.Add(LobyButton_R_1);
	else
		EI_LOG(Warning, TEXT("[UEIWidget_LobyButton] LobyButton_R_1 is nullptr"));

	UEIWidget_LobyButton* LobyButton_R_2 = Cast<UEIWidget_LobyButton>(GetWidgetFromName(TEXT("Loby_Select_button_R_2")));
	if (LobyButton_R_2 != nullptr && LobyButton_R_2->IsValidLowLevel() == true)
		m_MenuButtonList_R.Add(LobyButton_R_2);
	else
		EI_LOG(Warning, TEXT("[UEIWidget_LobyButton] LobyButton_R_2 is nullptr"));
	//---- R 버튼 END----	
}
