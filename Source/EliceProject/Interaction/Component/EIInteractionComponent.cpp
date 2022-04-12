// Fill out your copyright notice in the Description page of Project Settings.

#include "Interaction/Component/EIInteractionComponent.h"

#include "Net/UnrealNetwork.h"

#include "Library_System/EIFunctionLibrary_System.h"
#include "Interaction/Interface/EIInteractionSystem.h"

UEIInteractionComponent::UEIInteractionComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	SetIsReplicatedByDefault(true);
}

void UEIInteractionComponent::BeginPlay()
{
	Super::BeginPlay();

	UEIInteractionSystem* InteractionSystem = UEIFunctionLibrary_System::GetInteractionSystem(GetOwner()->GetWorld());
	if (InteractionSystem == nullptr || InteractionSystem->IsValidLowLevel() == false)
		return;




	//InteractionSystem->Please();
	//Test();
	
	//Test
	/*FInteractionEvent BeginOverlap;
	BeginOverlap.BindUFunction(this, TEXT("Test"));

	InteractionSystem->Bind_BeginOverlap(EIInteractionObjectType::None, BeginOverlap);*/
	//Test

	UE_LOG(LogTemp, Warning, TEXT("m_CheckTimerStart = %d"), m_CheckTimeStart);
}

void UEIInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (false == m_StartTime)
	{
		m_ActiveTimer += DeltaTime;
		UE_LOG(LogTemp, Warning, TEXT("Timer : %f"), m_ActiveTimer);

		if (m_ActiveTime <= m_ActiveTimer)
		{
			m_ActiveTimer = 0.f;
			m_StartTime = true;

			if (GetOwner()->HasAuthority() == true)
				m_CheckTimeStart = true;
			if (GetOwner()->HasAuthority() == false)
				UE_LOG(LogTemp, Warning, TEXT("m_CheckTimerStart = %d"), m_CheckTimeStart);
		}
	}
}

void UEIInteractionComponent::GetLifetimeReplicatedProps(TArray< FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UEIInteractionComponent, m_CheckTimeStart);
}

//* Overlap한 인터랙션 찾기 */
void UEIInteractionComponent::SearchInteraction()
{
	//Owner가 캐릭터인 경우


	//Owner가 Object인 경우
}

//* 인터랙션 정보 업데이트 */
void UEIInteractionComponent::UpdateInteractionData()
{
	SearchInteraction();
}

void UEIInteractionComponent::Test()
{
	UEIInteractionSystem* InteractionSystem = UEIFunctionLibrary_System::GetInteractionSystem(GetOwner()->GetWorld());
	if (InteractionSystem == nullptr || InteractionSystem->IsValidLowLevel() == false)
		return;

	InteractionSystem->DediTest();

}
void UEIInteractionComponent::Please()
{
	UEIInteractionSystem* InteractionSystem = UEIFunctionLibrary_System::GetInteractionSystem(GetOwner()->GetWorld());
	if (InteractionSystem == nullptr || InteractionSystem->IsValidLowLevel() == false)
		return;

	//if (false == GetOwner()->HasAuthority())
	if (GetOwner()->GetNetMode() == NM_Client)
		InteractionSystem->Please();
}
