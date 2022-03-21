// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "EIInteraction.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UEIInteraction : public UInterface
{
	GENERATED_BODY()
};

/**
 * TO DO : 상호작용, 퍼즐등을 위한 인터랙션 인터페이스
 */
class ELICEPROJECT_API IEIInteraction
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	IEIInteraction();

public:
	virtual bool IsOverlapInteraction() = 0;
	virtual bool IsEnableInteraction() = 0;

	virtual void UpdateInteractionState() = 0;
	virtual void Interaction_BeginOverlap() = 0;
	virtual void Interaction_Execute() = 0;
	virtual void Interaction_EndOverlap() = 0;
};
