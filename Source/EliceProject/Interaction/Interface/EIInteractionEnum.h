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
enum class EIInteractionObjectType : uint8
{
    None,
};