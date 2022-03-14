// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Common/EIGameCharacter.h"
#include "EINPC.generated.h"

/**
 * 
 */
UCLASS()
class ELICEPROJECT_API AEINPC : public AEIGameCharacter
{
	GENERATED_BODY()
	
public:
	AEINPC();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
};
