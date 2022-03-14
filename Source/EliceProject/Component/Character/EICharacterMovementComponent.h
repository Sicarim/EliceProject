// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "EICharacterMovementComponent.generated.h"

/**
 * TO DO : CharacterMovement Component
 */
UCLASS()
class ELICEPROJECT_API UEICharacterMovementComponent : public UCharacterMovementComponent
{
	GENERATED_BODY()
	
public:
	UEICharacterMovementComponent();

protected:
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	void ForceMove();
	void SpecialMove();
};
