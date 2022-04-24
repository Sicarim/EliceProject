// Fill out your copyright notice in the Description page of Project Settings.

#include "Interaction/Component/EIInteractionComponent.h"

#include "Net/UnrealNetwork.h"

#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Components/CapsuleComponent.h"
#include "Library_System/EIFunctionLibrary_System.h"
#include "Interaction/Interface/EIInteractionSystem.h"

#include "Character/Common/EIGameCharacter.h"
#include "Interaction/Actor/EIInteractionBaseActor.h"

UEIInteractionComponent::UEIInteractionComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	SetIsReplicatedByDefault(true);
}

void UEIInteractionComponent::BeginPlay()
{
	Super::BeginPlay();

	SetUpInteraction();

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
}

void UEIInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	SearchInteraction();
}

void UEIInteractionComponent::GetLifetimeReplicatedProps(TArray< FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

}

//----------------------------Public----------------------------//
//* Interaction 실행 */
bool UEIInteractionComponent::NotifyInteractionEvent(AActor* InActor, EIInteractionEventType InEventType)
{
	return true;
}
//--------------------------Public_END--------------------------//


//----------------------------Protected----------------------------//
//* Overlap한 인터랙션 찾기 */
void UEIInteractionComponent::SearchInteraction()
{
	TArray<FHitResult> OutHits, AppendHitList;

	//Owner가 캐릭터인 경우
	if (EIInteractionOwnerType::Interaction_Doer == m_OwnerType)
	{
		AEIGameCharacter* Character = Cast<AEIGameCharacter>(GetOwner());
		if (nullptr == Character || false == Character->IsValidLowLevel())
		{
			UE_LOG(LogTemp, Warning, TEXT("m_CachedCharacter is nullptr"));
			return;
		}

		UCapsuleComponent* CharacterCapsule = Character->GetCapsuleComponent();
		if (nullptr == CharacterCapsule || false == CharacterCapsule->IsValidLowLevel())
		{
			UE_LOG(LogTemp, Warning, TEXT("CapsuleComponent is nullptr"));
			return;
		}

		float Radius = CharacterCapsule->GetScaledCapsuleRadius();
		float HalfHeight = CharacterCapsule->GetScaledCapsuleHalfHeight();

		FVector StartTrace = Character->GetActorLocation() + FVector(0.f, 0.f, Radius - HalfHeight);
		FVector EndTrace = Character->GetActorLocation() + FVector(0.f, 0.f, HalfHeight - Radius);

		TArray<AActor*> IgnoreActorList;
		IgnoreActorList.Add(GetOwner());

		//충돌 체크
		UKismetSystemLibrary::CapsuleTraceMultiByProfile(GetOuter(), StartTrace, EndTrace, Radius, HalfHeight, "Interaction", false, IgnoreActorList, EDrawDebugTrace::None, OutHits, true);

		AppendHitList.Append(OutHits);
	}
	//Owner가 Object인 경우
	else if (EIInteractionOwnerType::Interaction_Object == m_OwnerType)
	{
		//오브젝트가 주체인 경우 해당 내용 구현
	}

	//인터랙션 정보 업데이트
	UpdateInteractionData(AppendHitList);
}

//* 인터랙션 정보 업데이트 */
void UEIInteractionComponent::UpdateInteractionData(TArray<FHitResult>& InHitList)
{		
	EIInteractionEventType ChangedEvent = EIInteractionEventType::None;

	//EndOverlap시
	for (FEIInteractionData& Data : m_InteractionDataList)
	{
	}

	//BeginOverlap시
	for (const FHitResult& Data : InHitList)
	{
		FEIInteractionData BeginData;

		//데이터가 먼저 있는지 확인
		FEIInteractionData* FindData = m_InteractionDataList.FindByPredicate([Data](const FEIInteractionData& Data)
			{
				return true; 
			});

		BeginData.m_InteractionActor = Data.Actor.Get();
		BeginData.m_CurrentState = EIInteractionStateType::BeginInteraction;

		m_CachedInterationDataList.Add(BeginData);
		m_InteractionDataList.Append(m_CachedInterationDataList);
	}
	
	//인터랙션 실행
	if (m_InteractionDataList.Num() != 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("not impty"));
	}

}
//--------------------------Protected_END--------------------------//

//----------------------------Private----------------------------//
void UEIInteractionComponent::SetUpInteraction()
{
	AActor* Owner = GetOwner();
	if (nullptr == Owner || false == Owner->IsValidLowLevel())
		return;

	//Owner가 캐릭터
	if (Cast<AEIGameCharacter>(Owner))
	{
		SetComponentTickEnabled(true);
	}
	//Owner가 오브젝트
	else if (Cast<AEIInteractionBaseActor>(Owner))
	{
		SetComponentTickEnabled(false);
		Owner->SetActorTickEnabled(false);
	}
}
//--------------------------Private_END--------------------------//

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






