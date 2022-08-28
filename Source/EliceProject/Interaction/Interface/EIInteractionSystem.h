// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Interaction/Interface/EIInteractionEnum.h"
#include "EIInteractionSystem.generated.h"

/**
 * TO DO : Intance에 추가할 InteractionSystem
 */

class UWorld;

class UEIGameInstance;
class UEIInteractionComponent;

DECLARE_DELEGATE_ThreeParams(FInteractionEvent, AActor*, EIInteractionObjectType, AActor*)
DECLARE_MULTICAST_DELEGATE_ThreeParams(FBeginOverlapEvent, AActor*, EIInteractionObjectType, AActor*)
DECLARE_MULTICAST_DELEGATE_ThreeParams(FExecuteEvent, AActor*, EIInteractionObjectType, AActor*)
DECLARE_MULTICAST_DELEGATE_ThreeParams(FEndOverlapEvent, AActor*, EIInteractionObjectType, AActor*)

USTRUCT(BlueprintType)
struct FEIInteractionInfo
{
	GENERATED_BODY()

public:
	UPROPERTY()
	int32 Key;

	UPROPERTY()
	UEIInteractionComponent* InteractionComponent;

public:
	FEIInteractionInfo()
	{
		Key = 0;
		InteractionComponent = nullptr;
	}
};

UCLASS()
class ELICEPROJECT_API UEIInteractionSystem : public UObject
{
	GENERATED_BODY()
	
public:
	UEIInteractionSystem();

public:
	//* Interaction Add */
	void AddInteraction(UEIInteractionComponent* InComponent);

	//* Interaction Remove */
	void RemoveInteraction(UEIInteractionComponent* InComponent);

	//* Interaction Dedi */
	UFUNCTION(Server, Reliable)
	void Server_InteractionListSync(const TArray<FEIInteractionInfo>& InArray);
	void Server_InteractionListSync_Implementation(const TArray<FEIInteractionInfo>& InArray);

	UFUNCTION(Client, Reliable)
	void Client_InteractionListSync(const TArray<FEIInteractionInfo>& InArray);
	void Client_InteractionListSync_Implementation(const TArray<FEIInteractionInfo>& InArray);

	UFUNCTION(NetMulticast, Reliable)
	void NetMulticast_InteractionListSync(const TArray<FEIInteractionInfo>& InArray);
	void NetMulticast_InteractionListSync_Implementation(const TArray<FEIInteractionInfo>& InArray);
	
	//* Interaction Bind */
	void Bind_BeginOverlap(EIInteractionObjectType InType, const FInteractionEvent& InDelegate);
	void Bind_Execute(EIInteractionObjectType InType, const FInteractionEvent& InDelegate);
	void Bind_EndOverlap(EIInteractionObjectType InType, const FInteractionEvent& InDelegate);

	//* Interaction UnBind */

	//* Interaction BroadCast */
	void BroadCast_BeginOverlap(AActor* InFirst, EIInteractionObjectType InType, AActor* InSecond);
	void BroadCast_ExecuteOverlap(AActor* InFirst, EIInteractionObjectType InType, AActor* InSecond);
	void BroadCast_EndOverlap(AActor* InFirst, EIInteractionObjectType InType, AActor* InSecond);

private:
	UWorld* InstanceGetWorld();

protected:
	//TMap<int32, UEIInteractionComponent*> m_InteractionList;
	TArray<FEIInteractionInfo> m_InteractionList;
	TMap<int32, UEIInteractionComponent*> m_SpecialInteracrtion;

	TMap<EIInteractionObjectType, FBeginOverlapEvent> m_BeginOverlapList;
	TMap<EIInteractionObjectType, FExecuteEvent> m_ExecuteList;
	TMap<EIInteractionObjectType, FEndOverlapEvent> m_EndOverlapList;

private:
	UEIGameInstance* m_GameInstance;
	int32 m_InteractionKey = 0;
};
