// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Interaction/Interface/EIInteractionEnum.h"
#include "EIInteractionComponent.generated.h"

class AActor;
class AEIGameCharacter;

USTRUCT(BlueprintType)
struct FEIInteractionData
{
	GENERATED_BODY()

public:
	UPROPERTY()
	AActor* m_InteractionActor;

	UPROPERTY()
	EIInteractionStateType m_CurrentState;

	UPROPERTY()
	EIInteractionStateType m_BeforeState;

	UPROPERTY()
	UPrimitiveComponent* m_OverlapComponent;

	FEIInteractionData()
	{
		m_InteractionActor = nullptr;
		m_CurrentState = EIInteractionStateType::None;
		m_BeforeState = EIInteractionStateType::None;
		m_OverlapComponent = nullptr;
	}
};

UCLASS(BlueprintType, Blueprintable)
class ELICEPROJECT_API UEIInteractionComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UEIInteractionComponent();

protected:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason);
	//virtual void PreReplication(IRepChangedPropertyTracker& ChangedPropertyTracker) override;
	virtual void GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const override;

public:
	// >> Get
	FORCEINLINE const EIInteractionObjectType GetInteractionObjectType() const { return m_InteractionObjectType; }
	FORCEINLINE const EIInteractionOperateType GetInteractionOperateType() const { return m_InteractionOperateType; }
	FORCEINLINE const int32 GetInteractionKey() const { return m_InteractionKey; }
	FORCEINLINE TArray<FEIInteractionData> GetInteractionDataList() { return m_InteractionDataList; }
	// <<

	// >> Set
	FORCEINLINE void SetInteractionOwnerType(EIInteractionOwnerType InOwnerType) { m_OwnerType = InOwnerType; }
	FORCEINLINE void SetInteractionObjectType(EIInteractionObjectType InObjectType) { m_InteractionObjectType = InObjectType; }
	// <<

	// >> Common
	bool NotifyInteractionEvent(AActor* InInteractionCharacter, AActor* InInteractionActor, EIInteractionEventType InEventType);
	void OnInsertionInteractionData(AActor* InActor, EIInteractionEventType InEventType);
	void SetupInteractionState(FEIInteractionData* InData, EIInteractionEventType InEventType);
	void OnRemoveInteractionData(AActor* InActor);
	// <<

protected:
	void SearchInteraction();
	void UpdateInteractionData(TArray<FHitResult>& InHitList);
	void SetupLinkEvent();

private:
	void SetUpInteraction();

	UFUNCTION(Server, Reliable)
	void Server_AddUndefineData(const TArray<FEIInteractionData>& InBeginOverlapList);

#if WITH_EDITOR
protected:
	virtual void PostEditChangeProperty(struct FPropertyChangedEvent& InPropertyName);
#endif // WITH_EDITOR


protected:
	UPROPERTY(EditAnyWhere, Category = "InteractionBaseOption|Base Option", meta = (DisplayName = "Object Type", ToolTip = "인터랙션 타입"))
	EIInteractionObjectType m_InteractionObjectType = EIInteractionObjectType::None;

	UPROPERTY(EditAnyWhere, Category = "InteractionBaseOption|Base Option", meta = (DisplayName = "Operate Type", ToolTip = "인터랙션 실행타입"))
	EIInteractionOperateType m_InteractionOperateType = EIInteractionOperateType::OnClient;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "InteractionBaseOption|Link Option", meta = (ToolTip = "링크된 부모 인터랙션"))
	TArray<AActor*> m_LinkParentActor;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "InteractionBaseOption|Link Option", meta = (ToolTip = "링크된 자식 인터랙션"))
	TArray<AActor*> m_LinkOffspringActor;

	EIInteractionOwnerType m_OwnerType = EIInteractionOwnerType::None;

	UPROPERTY()
	int32 m_InteractionKey = -1;

private:
	UPROPERTY(Transient)
	TArray<FEIInteractionData> m_InteractionDataList;

	//결정되지 않는 데이터
	UPROPERTY(Transient)
	TArray<FEIInteractionData> m_UnDefineInteractionDataList;

	
};
