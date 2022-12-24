// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

//Level Define
UENUM(BlueprintType)
enum class EIProcedureType : uint8
{
    None,
    PersistentLevelLoad   UMETA(DisplayName = "�۽ý���Ʈ���� �ε�"),
    SubLevelLoad          UMETA(DisplayName = "���극�� �ε�"),
};