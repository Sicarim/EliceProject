// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Interaction/Interface/EIInteractionSystem.h"
#include "Interaction/Interface/EIInteractionEnum.h"
#include "EIInteractionComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ELICEPROJECT_API UEIInteractionComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UEIInteractionComponent();

protected:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual void GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const;

protected:
	void SearchInteraction();
	void UpdateInteractionData();
		
protected:
	UFUNCTION()
	void Test();
	void Please();

protected:
	UPROPERTY(Replicated)
	bool m_CheckTimeStart = false;

	float m_ActiveTime = 10.f;
	float m_ActiveTimer = 0.f;
	bool m_StartTime = false;
};
