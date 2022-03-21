// Fill out your copyright notice in the Description page of Project Settings.

#include "Interaction/Interface/EIInteractionSystem.h"

UEIInteractionSystem::UEIInteractionSystem()
{

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

void UEIInteractionSystem::BroadCast_BeginOverlap(EIInteractionObjectType InType)
{
    //m_BeginOverlapList.Find(InType)->Broadcast(InType);
}

void UEIInteractionSystem::BroadCast_ExecuteOverlap()
{

}

void UEIInteractionSystem::BroadCast_EndOverlap()
{

}

