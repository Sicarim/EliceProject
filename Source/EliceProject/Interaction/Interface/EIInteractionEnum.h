// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class EIInteractionEventType : uint8
{
    None,
    BeginOverlap    UMETA(DisplayName = "겹쳤을때"),
    Execute         UMETA(DisplayName = "실행했을때"),
    EndOverlap      UMETA(DisplayName = "빠져나왔을때"),
};

UENUM(BlueprintType)
enum class EIInteractionStateType : uint8
{
    None,
    BeginOverlapInteraction     UMETA(DisplayName = "인터랙션 진입"),
    EnableInteraction           UMETA(DisplayName = "인터랙션 가능"),
    EndOverlapInteraction       UMETA(DisplayName = "인터랙션 탈출"),
    DisableInteraction          UMETA(DisplayName = "인터랙션 불가능"),
    StartInteraction            UMETA(DisplayName = "인터랙션 시작"),
    RunningInteraction          UMETA(DisplayName = "인터랙션 실행 중"),
    EndInteraction              UMETA(DisplayName = "인터랙션 종료"),
};

UENUM(BlueprintType)
enum class EIInteractionOwnerType : uint8
{
    None,
    Interaction_Doer        UMETA(DisplayName = "인터랙션 주체자"),
    Interaction_Object      UMETA(DisplayName = "인터랙션 행위자"),
};

UENUM(BlueprintType)
enum class EIInteractionOperateType : uint8
{
    None,
    OnClient        UMETA(DisplayName = "클라이언트"),
    OnServer        UMETA(DisplayName = "서버"),
};

UENUM(BlueprintType)
enum class EIInteractionObjectType : uint8
{
    None,
    Character     UMETA(DisplayName = "캐릭터"),
    Puzzle        UMETA(DisplayName = "퍼즐"),
};