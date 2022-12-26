// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/PlayerCameraManager.h"
#include "EICameraManager.generated.h"

/**
 * CameraManager - 카메라 관리
 */

UCLASS()
class ELICEPROJECT_API AEICameraManager : public APlayerCameraManager
{
	GENERATED_BODY()
	
public:
	AEICameraManager();
};
