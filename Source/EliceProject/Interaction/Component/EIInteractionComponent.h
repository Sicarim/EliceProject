// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Interaction/Interface/EIInteractionEnum.h"
#include "EIInteractionComponent.generated.h"

class AEIGameCharacter;

USTRUCT(BlueprintType)
struct FEIInteractionData
{
	GENERATED_BODY()

public:
	UPROPERTY()
	AActor* m_InteractionActor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EIInteractionStateType m_CurrentState = EIInteractionStateType::None;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EIInteractionStateType m_BeforeState = EIInteractionStateType::None;

	FEIInteractionData()
	{
		m_InteractionActor = nullptr;
		m_CurrentState = EIInteractionStateType::None;
		m_BeforeState = EIInteractionStateType::None;
	}
};

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class ELICEPROJECT_API UEIInteractionComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UEIInteractionComponent();

protected:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual void GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const;

public:
	// Get
	FORCEINLINE const EIInteractionObjectType GetInteractionObjectType() { return m_InteractionObjectType; }

	// Set
	FORCEINLINE void SetInteractionOwnerType(EIInteractionOwnerType InOwnerType) { m_OwnerType = InOwnerType; }
	FORCEINLINE void SetInteractionObjectType(EIInteractionObjectType InObjectType) { m_ObjectType = InObjectType; }

protected:
	void SearchInteraction();
	void UpdateInteractionData(TArray<FHitResult>& InHitList);

private:
	void SetUpInteraction();
		
protected:
	UFUNCTION()
	void Test();
	void Please();

protected:
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "InteractionBaseOption")
	EIInteractionObjectType m_InteractionObjectType = EIInteractionObjectType::None;

	EIInteractionOwnerType m_OwnerType = EIInteractionOwnerType::None;
	EIInteractionObjectType m_ObjectType = EIInteractionObjectType::None;

private:
	UPROPERTY()
	TArray<FEIInteractionData> m_InteractionDataList;
};
