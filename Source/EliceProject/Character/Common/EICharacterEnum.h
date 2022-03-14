// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class EICharacterCameraType : uint8
{
    None,
    DefaultCamera      UMETA(DisplayName = "기본 카메라"),
};