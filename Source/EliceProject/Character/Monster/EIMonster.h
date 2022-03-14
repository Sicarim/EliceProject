// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Common/EIGameCharacter.h"
#include "EIMonster.generated.h"

/**
 * 
 */
UCLASS()
class ELICEPROJECT_API AEIMonster : public AEIGameCharacter
{
	GENERATED_BODY()
	
public:
	AEIMonster();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
};
