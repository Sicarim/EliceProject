// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EICharacter.generated.h"

class UInputComponent;

UCLASS()
class ELICEPROJECT_API AEICharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AEICharacter();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	//-------------------------------------------------------//

protected:
	void IsInteractionKey();

	//Base Move
	void MoveForward(float InAxisValue);
	void MoveRight(float InAxisValue);
	void LookUp(float InAxisValue);
	void Turn(float InAxisValue);
	//-------------------------------------------------------//

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Camera)
	float m_BaseTurnRate = 45.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Camera)
	float m_BaseLookUpRate = 45.f;

	bool m_IsWalk;
	bool m_IsFoward;
	bool m_IsRight;
};
