// Fill out your copyright notice in the Description page of Project Settings.

#include "Interaction/Interface/EIInteractionSystem.h"

#include "Net/UnrealNetwork.h"
#include "Kismet/GameplayStatics.h"


#include "GameInstance/EIGameInstance.h"
#include "Interaction/Component/EIInteractionComponent.h"

UEIInteractionSystem::UEIInteractionSystem()
{

}

//----------------------------Public----------------------------//
void UEIInteractionSystem::AddInteraction(UEIInteractionComponent* InComponent)
{
    FEIInteractionInfo InteractionInfo;

    InteractionInfo.Key = m_InteractionKey++;
    InteractionInfo.InteractionComponent = InComponent;

    m_InteractionList.Add(InteractionInfo);
    
    int32 Key = InComponent->GetInteractionKey();
    if (Key != -1)
    {
        if (false == m_SpecialInteracrtion.Contains(Key))
        {
            m_SpecialInteracrtion.FindOrAdd(Key) = InComponent;
        }
    }
}

void UEIInteractionSystem::RemoveInteraction(UEIInteractionComponent* InComponent)
{
    //To do
}

void UEIInteractionSystem::Server_InteractionListSync_Implementation(const TArray<FEIInteractionInfo>& InArray)
{
    m_InteractionList = InArray;
    Client_InteractionListSync(m_InteractionList);
    NetMulticast_InteractionListSync(m_InteractionList);
    //if (GetWorld()->GetNetMode() == NM_Client)
    {
        UE_LOG(LogTemp, Warning, TEXT("NetMode :: Client  ListCount : %d"), m_InteractionList.Num());
    }
}

void UEIInteractionSystem::Client_InteractionListSync_Implementation(const TArray<FEIInteractionInfo>& InArray)
{
    m_InteractionList = InArray;
    //Server_InteractionListSync(m_InteractionList);
    NetMulticast_InteractionListSync(m_InteractionList);
   // if (GetWorld()->GetNetMode() == NM_Client)
    {
        UE_LOG(LogTemp, Warning, TEXT("NetMode :: Client  ListCount : %d"), m_InteractionList.Num());
    }
}

void UEIInteractionSystem::NetMulticast_InteractionListSync_Implementation(const TArray<FEIInteractionInfo>& InArray)
{
    m_InteractionList = InArray;
    //if (GetWorld()->GetNetMode() == NM_Client)
    {
        UE_LOG(LogTemp, Warning, TEXT("NetMode :: Client  ListCount : %d"), m_InteractionList.Num());
    }
}

void UEIInteractionSystem::Bind_BeginOverlap(EIInteractionObjectType InType, const FInteractionEvent& InDelegate)
{
    m_BeginOverlapList.FindOrAdd(InType).Add(InDelegate);
}

void UEIInteractionSystem::Bind_Execute(EIInteractionObjectType InType, const FInteractionEvent& InDelegate)
{
    m_ExecuteList.FindOrAdd(InType).Add(InDelegate);
}

void UEIInteractionSystem::Bind_EndOverlap(EIInteractionObjectType InType, const FInteractionEvent& InDelegate)
{
    m_EndOverlapList.FindOrAdd(InType).Add(InDelegate);
}

void UEIInteractionSystem::BroadCast_BeginOverlap(AActor* InFirst, EIInteractionObjectType InType, AActor* InSecond)
{
    m_BeginOverlapList.Find(InType)->Broadcast(InFirst, InType, InSecond);
}

void UEIInteractionSystem::BroadCast_ExecuteOverlap(AActor* InFirst, EIInteractionObjectType InType, AActor* InSecond)
{
    m_ExecuteList.Find(InType)->Broadcast(InFirst, InType, InSecond);
}

void UEIInteractionSystem::BroadCast_EndOverlap(AActor* InFirst, EIInteractionObjectType InType, AActor* InSecond)
{
    m_EndOverlapList.Find(InType)->Broadcast(InFirst, InType, InSecond);
}
//--------------------------Public_END--------------------------//


//----------------------------Protected----------------------------//

//--------------------------Protected_END--------------------------//

//----------------------------Private----------------------------//
UWorld* UEIInteractionSystem::InstanceGetWorld()
{
    m_GameInstance = Cast<UEIGameInstance>(UGameplayStatics::GetGameInstance(this));
    if (nullptr == m_GameInstance)
        return nullptr;

    return m_GameInstance->GetWorld();
}
//--------------------------Private_END--------------------------//