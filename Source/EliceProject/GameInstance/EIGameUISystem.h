// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/WidgetTree.h"
#include "GameInstance/EIUIDefine.h"
#include "EIGameUISystem.generated.h"

/**
 * UI 생성 및 관리하는 UISytem
 */

class UEITable;

UCLASS()
class ELICEPROJECT_API UEIGameUISystem : public UWidgetTree
{
	GENERATED_BODY()
	
public:
	UEIGameUISystem();

public:
	UUserWidget* Show(UObject* WorldContextObject, EIWidgetType InWidgetType);
	void Hide(EIWidgetType InWidgetType);

protected:
	void InitUIData(UObject* WorldContextObject);

private:
	UPROPERTY()
	UEITable* m_Table = nullptr;

	UPROPERTY(Transient)
	TArray<UUserWidget*> m_ShowWidgetList;
};
