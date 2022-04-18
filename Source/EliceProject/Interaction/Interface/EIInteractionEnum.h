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
enum class EIInteractionOwnerType : uint8
{
    None,
    Interaction_Doer        UMETA(DisplayName = "인터랙션 주체자"),
    Interaction_Object      UMETA(DisplayName = "인터랙션 행위자"),
};

UENUM(BlueprintType)
enum class EIInteractionObjectType : uint8
{
    None,
    Puzzle        UMETA(DisplayName = "퍼즐"),
};