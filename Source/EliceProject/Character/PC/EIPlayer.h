// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/Common/EIGameCharacter.h"
#include "Character/Common/EICharacterEnum.h"
#include "EIPlayer.generated.h"

/**
 * To DO : 플레이어
 */

class UCameraComponent;
class USpringArmComponent;
class AEIPlayerController;

UCLASS()
class ELICEPROJECT_API AEIPlayer : public AEIGameCharacter
{
	GENERATED_BODY()
	
public:
	AEIPlayer();

protected:
	virtual void PostInitializeComponents() override;

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	//------------------------------------------------------------------//
	
public:
	void SetCameraMode();

protected:
	UPROPERTY(EditAnywhere, Category = "Camera")
	UCameraComponent* m_MainCamera;

	UPROPERTY(EditAnywhere, Category = "Camera")
	USpringArmComponent* m_MainCameraArm;

	UPROPERTY()
	AEIPlayerController* m_PlayerController;

	float m_ArmLengthTo;
	//UPROPERTY(VisibleAnywhere, Category = "Stat")
		//class UPlayerStatComponent* playerStat_;

private:
	EICharacterCameraType m_CameraType = EICharacterCameraType::DefaultCamera;
};
