// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

//Level Define
UENUM(BlueprintType)
enum class EIProcedureType : uint8
{
    None,
    PersistentLevelLoad   UMETA(DisplayName = "퍼시스턴트레벨 로딩"),
    SubLevelLoad          UMETA(DisplayName = "서브레벨 로딩"),
};