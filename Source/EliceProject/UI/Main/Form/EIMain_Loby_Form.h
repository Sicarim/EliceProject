// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameInstance/EIUIDefine.h"
#include "EIMain_Loby_Form.generated.h"

/**
 * Loby À§Á¬.
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

protected:
	UFUNCTION()
	void Clicked_MatcingButton();

	UFUNCTION()
	void Clicked_BagButton();

	UFUNCTION()
	void Clicked_ExitButton();

private:
	UPROPERTY()
	UEIWidget_LobyButton* m_MatchingButton = nullptr;

	UPROPERTY()
	UEIWidget_LobyButton* m_BagButton = nullptr;

	UPROPERTY()
	UEIWidget_LobyButton* m_ExitButton = nullptr;
};
