// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EIMain_Loby_Form.generated.h"

/**
 * Loby 위젯.
 */

class UEIWidget_LobyButton;

UCLASS()
class ELICEPROJECT_API UEIMain_Loby_Form : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UEIMain_Loby_Form(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void NativeConstruct() override;

private:
	//왼쪽 버튼
	TArray<UEIWidget_LobyButton*> m_MenuButtonList_L;

	//오른쪽 버튼.
	TArray<UEIWidget_LobyButton*> m_MenuButtonList_R;
};
