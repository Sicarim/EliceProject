// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

DECLARE_LOG_CATEGORY_EXTERN(EliceProject, Log, All);
#define EI_LOG_CALLINFO (FString(__FUNCTION__) + TEXT("(") + FString::FromInt(__LINE__) + TEXT(")"))
#define EILOGS(Verbosity) UE_LOG(EliceProject, Verbosity, TEXT("%s"), *EI_LOG_CALLINFO)
#define EI_LOG(Verbosity, Format, ...) UE_LOG(EliceProject, Verbosity, TEXT("%s %s"), *EI_LOG_CALLINFO, *FString::Printf(Format, ##__VA_ARGS__))
#define EI_CHECK(Expr, ...) { if (!(Expr)) { EI_LOG(Error, TEXT("ASSERTION : %s"), TEXT("'"#Expr"'")); return __VA_ARGS__; } }