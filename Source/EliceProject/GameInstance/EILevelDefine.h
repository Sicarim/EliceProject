// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

//Open Level Type
UENUM(BlueprintType)
enum class EIOpenLevelType : uint8
{
    None,
    Main_Loby        UMETA(DisplayName = "메인 로비"),
    War_Place        UMETA(DisplayName = "대결 장소"),
};

//Level Define
UENUM(BlueprintType)
enum class EIProcedureType : uint8
{
    None,
    PersistentLevelLoad   UMETA(DisplayName = "퍼시스턴트레벨 로딩"),
    SubLevelLoad          UMETA(DisplayName = "서브레벨 로딩"),
    AllLevelLoad          UMETA(DisplayName = "모든 레벨 완료 체크"),
    Teleport              UMETA(DisplayName = "텔레포트"),
};