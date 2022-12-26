// Fill out your copyright notice in the Description page of Project Settings.

#include "GameInstance/EIGameUISystem.h"

#include "Table/EITable.h"
#include "Table/EIUIData.h"
#include "Library_System/EIFunctionLibrary_System.h"

//Main Loby
#include "UI/Main/Form/EIMain_Loby_Form.h"

UEIGameUISystem::UEIGameUISystem()
{
	
}

void UEIGameUISystem::InitUIData(UObject* WorldContextObject)
{
	if (WorldContextObject == nullptr || WorldContextObject->IsValidLowLevel() == false)
	{
		EI_LOG(Warning, TEXT("[UEIGameUISystem] WorldContextObject is nullptr"));
		return;
	}
	
	m_Table = UEIFunctionLibrary_System::GetTable(WorldContextObject);
	if (m_Table == nullptr || m_Table->IsValidLowLevel() == false)
	{
		EI_LOG(Warning, TEXT("[UEIGameUISystem] Table is nullptr"));
		return;
	}
}

UUserWidget* UEIGameUISystem::Show(UObject* WorldContextObject, EIWidgetType InWidgetType)
{
	if (WorldContextObject == nullptr || WorldContextObject->IsValidLowLevel() == false)
	{
		EI_LOG(Warning, TEXT("[UEIGameUISystem] WorldContextObject is nullptr"));
		return nullptr;
	}

	if (m_Table == nullptr || m_Table->IsValidLowLevel() == false)
		InitUIData(WorldContextObject);

	if (m_Table == nullptr || m_Table->IsValidLowLevel() == false)
	{
		EI_LOG(Warning, TEXT("[UEIGameUISystem] Table is nullptr"));
		return nullptr;
	}

	FEIUIData UIData;
	m_Table->GetUIDataAt(InWidgetType, UIData);

	UObject* LoadObject = UIData.ui_bp_path.TryLoad();
	if (LoadObject == nullptr || LoadObject->IsValidLowLevel() == false)
	{
		EI_LOG(Warning, TEXT("[UEIGameUISystem] LoadObject is nullptr"));
		return nullptr;
	}

	TSubclassOf<UUserWidget> UserWidgetClass = LoadObject->GetClass();

	UClass* UIClass = Cast<UClass>(LoadObject);
	if (UIClass == nullptr || UIClass->IsValidLowLevel() == false)
	{
		EI_LOG(Warning, TEXT("[UEIGameUISystem] UIClass is nullptr"));
		return nullptr;
	}

	UUserWidget* ShowWidget = nullptr;
	ShowWidget = CreateWidget<UUserWidget>(this, UIClass);
	if (ShowWidget == nullptr || ShowWidget->IsValidLowLevel() == false)
	{
		EI_LOG(Warning, TEXT("[UEIGameUISystem] UIShowWidgetClass is nullptr"));
		return nullptr;
	}

	ShowWidget->AddToViewport();

	return ShowWidget;
}

void UEIGameUISystem::Hide(EIWidgetType InWidgetType)
{

}