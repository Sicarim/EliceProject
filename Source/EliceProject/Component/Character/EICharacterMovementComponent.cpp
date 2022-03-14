// Fill out your copyright notice in the Description page of Project Settings.

#include "EICharacterMovementComponent.h"

UEICharacterMovementComponent::UEICharacterMovementComponent()
{

}


void UEICharacterMovementComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}
//----------------------------Public----------------------------//
void UEICharacterMovementComponent::ForceMove()
{
    
}
//--------------------------Public_END--------------------------//

//----------------------------Protected----------------------------//
void UEICharacterMovementComponent::SpecialMove()
{
    if (nullptr != GetOwner() || false == GetOwner()->IsValidLowLevel())
        return;

    UE_LOG(LogTemp, Warning, TEXT("Owner Name : %s"), *GetOwner()->GetName());
}
//--------------------------Protected_END--------------------------//