// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

//UI Define
UENUM(BlueprintType)
enum class EIWidgetType : uint8
{
    None,
    MainLoby   UMETA(DisplayName = "메인 로비 UI"),
};

//Main Loby
UENUM(BlueprintType)
enum class EILobyButtonType : uint8
{
    None,
    Matching    UMETA(DisplayName = "매칭 버튼"),
    Bag         UMETA(DisplayName = "가방 버튼"),
    Exit        UMETA(DisplayName = "나가기 버튼"),
};