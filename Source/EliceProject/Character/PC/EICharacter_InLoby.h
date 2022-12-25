// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/Common/EIGameCharacter.h"
#include "Character/Common/EICharacterEnum.h"
#include "EICharacter_InLoby.generated.h"

/**
 * Loby 전용 캐릭터.
 */

class UCameraComponent;
class USpringArmComponent;
class AEIPlayerController;

UCLASS(Blueprintable, Blueprintable)
class ELICEPROJECT_API AEICharacter_InLoby : public AEIGameCharacter
{
	GENERATED_BODY()
	
public:
	AEICharacter_InLoby();

protected:
	virtual void PostInitializeComponents() override;

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void SetCameraMode();

protected:
	UPROPERTY(EditAnywhere, Category = "Camera")
	UCameraComponent* m_LobyCamera;

	UPROPERTY(EditAnywhere, Category = "Camera")
	USpringArmComponent* m_LobyCameraArm;

	float m_ArmLengthTo = 0.f;
	//-------------------------------------------------------/

private:
	EICharacterCameraType m_CameraType = EICharacterCameraType::DefaultCamera;
};
