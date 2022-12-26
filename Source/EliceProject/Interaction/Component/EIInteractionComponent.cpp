// Fill out your copyright notice in the Description page of Project Settings.

#include "Interaction/Component/EIInteractionComponent.h"

#include "Net/UnrealNetwork.h"

#include "Interaction/Interface/EIInteraction.h"

#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Components/CapsuleComponent.h"
#include "Library_System/EIFunctionLibrary_System.h"
#include "Interaction/Interface/EIInteractionSystem.h"

#include "Character/Common/EIGameCharacter.h"
#include "Interaction/Interface/EIInteraction.h"
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

	InteractionSystem->AddInteraction(this);
}

void UEIInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	SearchInteraction();
}

void UEIInteractionComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

void UEIInteractionComponent::GetLifetimeReplicatedProps(TArray< FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	//DOREPLIFETIME(UEIInteractionComponent, m_InteractionDataList);
}

//----------------------------Public----------------------------//
//* Interaction 실행 */
bool UEIInteractionComponent::NotifyInteractionEvent(AActor* InInteractionCharacter, AActor* InInteractionActor, EIInteractionEventType InEventType)
{
	AActor* Owner = GetOwner();
	if (nullptr == InInteractionCharacter || false == InInteractionCharacter->IsValidLowLevel())
		return false;

	if (nullptr == InInteractionActor || false == InInteractionActor->IsValidLowLevel())
		return false;

	AEIGameCharacter* Character = Cast<AEIGameCharacter>(InInteractionCharacter);
	if (nullptr == Character || false == Character->IsValidLowLevel())
		return false;
	
	AEIInteractionBaseActor* InteractionActor = Cast<AEIInteractionBaseActor>(Owner);
	if (nullptr == InteractionActor || false == InteractionActor->IsValidLowLevel())
		return false;

	//인터랙션 가능 상태인지 확인
	if (false == InteractionActor->IsEnableInteraction_Implementation(InInteractionCharacter, InEventType))
		return false;

	Character->Server_ExecuteInteractionEvent(InInteractionCharacter, InInteractionActor, InEventType);

	return true;
}

//* InteractionData 세팅 */
void UEIInteractionComponent::OnInsertionInteractionData(AActor* InActor, EIInteractionEventType InEventType)
{
	if (nullptr == InActor || false == InActor->IsValidLowLevel())
		return;

	FEIInteractionData* FindData = nullptr;

	//플레이어인 경우
	if (EIInteractionOwnerType::Interaction_Doer == m_OwnerType)
	{
		//먼저 결정되지 않는 인터랙션 목록에서 찾는다.
		FindData = m_UnDefineInteractionDataList.FindByPredicate([InActor](const FEIInteractionData& IsData)
			{
				return IsData.m_InteractionActor == InActor;
			});

		//없다면, 이미 데이터 리스트에 담겼으므로, 상태를 갱신한다.
		if (nullptr == FindData)
		{
			FEIInteractionData* CollectData = m_InteractionDataList.FindByPredicate([InActor](const FEIInteractionData& IsData)
				{
					return IsData.m_InteractionActor == InActor;
				});

			if (nullptr != CollectData)
			{
				//State 갱신
				SetupInteractionState(CollectData, InEventType);
			}
		}
		//찾았다면...
		else
		{
			//State 갱신
			SetupInteractionState(FindData, InEventType);
			m_InteractionDataList.Add(*FindData);

			m_UnDefineInteractionDataList.RemoveAll([InActor](const FEIInteractionData& IsData)
				{
					return IsData.m_InteractionActor == InActor;
				});
		}
	}
	//오브젝트인 경우
	else if (EIInteractionOwnerType::Interaction_Object == m_OwnerType)
	{
		AActor* Owner = GetOwner();

		//먼저 내가 데이터를 가지고 있는지 확인
		FindData = m_InteractionDataList.FindByPredicate([InActor](const FEIInteractionData& IsData)
			{
				return IsData.m_InteractionActor == InActor;
			});

		//없다면...
		if (nullptr == FindData)
		{
			//플레이어한테서 내 정보가 있는지 확인
			AEIGameCharacter* Character = Cast<AEIGameCharacter>(InActor);
			if (nullptr == Character || false == Character->IsValidLowLevel())
				return;

			UEIInteractionComponent* Comp = Character->GetInteractionComponent();
			if (nullptr == Comp || false == Comp->IsValidLowLevel())
				return;

			TArray<FEIInteractionData> InteractionDataList = Comp->GetInteractionDataList();
			FEIInteractionData* CollectData = InteractionDataList.FindByPredicate([Owner](const FEIInteractionData& IsData)
				{
					return IsData.m_InteractionActor == Owner;
				});

			if (nullptr != CollectData)
			{
				FEIInteractionData PlayerData;
				PlayerData.m_InteractionActor = Character;
				PlayerData.m_OverlapComponent = CollectData->m_OverlapComponent;

				//State 갱신
				SetupInteractionState(&PlayerData, InEventType);
				m_InteractionDataList.Add(PlayerData);
			}

			
		}
		//있다면 데이터 갱신
		else
		{
			//State 갱신
			SetupInteractionState(FindData, InEventType);
		}
	}
}

//* State 변경 */
void UEIInteractionComponent::SetupInteractionState(FEIInteractionData* InData, EIInteractionEventType InEventType)
{
	if (nullptr == InData)
		return;

	EIInteractionStateType BeforeStateType = InData->m_CurrentState;
	EIInteractionStateType CurrentStateType = EIInteractionStateType::None;

	switch (InEventType)
	{
	case EIInteractionEventType::BeginOverlap:
		CurrentStateType = EIInteractionStateType::BeginOverlapInteraction;
		break;

	case EIInteractionEventType::Execute:
		CurrentStateType = EIInteractionStateType::StartInteraction;
		break;

	case EIInteractionEventType::EndOverlap:
		CurrentStateType = EIInteractionStateType::EndOverlapInteraction;
		break;
	}

	InData->m_BeforeState = BeforeStateType;
	InData->m_CurrentState = CurrentStateType;
}

//* InteractionData 제거 */
void UEIInteractionComponent::OnRemoveInteractionData(AActor* InActor)
{
	m_InteractionDataList.RemoveAll([InActor](const FEIInteractionData& IsData)
		{
			return IsData.m_InteractionActor == InActor;
		});
}
//--------------------------Public_END--------------------------//

//----------------------------Protected----------------------------//
//* Overlap한 인터랙션 찾기 */
void UEIInteractionComponent::SearchInteraction()
{
	//충돌체크는 클라에서만
	ENetMode OwnerNetMode = GetOwner()->GetNetMode();
	if (ENetMode::NM_DedicatedServer == OwnerNetMode)
		return;

	TArray<FHitResult> OutHits, AppendHitList;

	//Owner가 캐릭터인 경우
	if (EIInteractionOwnerType::Interaction_Doer == m_OwnerType)
	{
		AEIGameCharacter* Character = Cast<AEIGameCharacter>(GetOwner());
		if (nullptr == Character || false == Character->IsValidLowLevel())
		{
			EI_LOG(Warning, TEXT("CachedCharacter is nullptr"));
			return;
		}

		UCapsuleComponent* CharacterCapsule = Character->GetCapsuleComponent();
		if (nullptr == CharacterCapsule || false == CharacterCapsule->IsValidLowLevel())
		{
			EI_LOG(Warning, TEXT("CapsuleComponent is nullptr"));
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

//* 인터랙션 정보 업데이트 및 실행 */
void UEIInteractionComponent::UpdateInteractionData(TArray<FHitResult>& InHitList)
{	
	TArray<FEIInteractionData> BeginOverlapList, EndOverlapList;

	//EndOverlap시
	for (FEIInteractionData& Data : m_InteractionDataList)
	{
		FHitResult* FindData = InHitList.FindByPredicate([Data](const FHitResult& IsData)
			{
				return IsData.Actor.Get() == Data.m_InteractionActor;
			});

		//데이터가 있으면 스킵
		if (nullptr != FindData)
			continue;

		FEIInteractionData EndData;
		EndData.m_InteractionActor = Data.m_InteractionActor;

		EndOverlapList.Add(EndData);
	}

	//BeginOverlap시
	for (const FHitResult& Data : InHitList)
	{
		//데이터가 먼저 있는지 확인
		FEIInteractionData* FindData = m_InteractionDataList.FindByPredicate([Data](const FEIInteractionData& IsData)
			{
				return IsData.m_InteractionActor == Data.Actor.Get();
			});

		//데이터가 있다면 스킵
		if (nullptr != FindData)
			continue;

		FEIInteractionData BeginData;
		BeginData.m_InteractionActor = Data.Actor.Get();
		BeginData.m_OverlapComponent = Data.GetComponent();

		BeginOverlapList.Add(BeginData);

		//결정되지 않은 데이터 캐싱
		m_UnDefineInteractionDataList.Append(BeginOverlapList);

		for (int32 i = 0; i < BeginOverlapList.Num(); i++)
		{
			EI_LOG(Warning, TEXT("Actor Name : %s %d"), *BeginOverlapList[i].m_InteractionActor->GetName(), BeginOverlapList.Num());
		}
	}

	//인터랙션 실행 - EndOverlap
	for (const FEIInteractionData& Data : EndOverlapList)
	{
		AEIInteractionBaseActor* InteractionActor = Cast<AEIInteractionBaseActor>(Data.m_InteractionActor);
		if (nullptr == InteractionActor || false == InteractionActor->IsValidLowLevel())
			continue;

		UEIInteractionComponent* InteractionComponent = InteractionActor->GetInteractionComponent();
		if (nullptr == InteractionComponent || false == InteractionComponent->IsValidLowLevel())
			continue;

		InteractionComponent->NotifyInteractionEvent(GetOwner(), InteractionActor, EIInteractionEventType::EndOverlap);
	}
	
	//인터랙션 실행 - BegineOverlap
	for (const FEIInteractionData& Data : BeginOverlapList)
	{
		AEIInteractionBaseActor* InteractionActor = Cast<AEIInteractionBaseActor>(Data.m_InteractionActor);
		if (nullptr == InteractionActor || false == InteractionActor->IsValidLowLevel())
			continue;

		UEIInteractionComponent* InteractionComponent = InteractionActor->GetInteractionComponent();
		if (nullptr == InteractionComponent || false == InteractionComponent->IsValidLowLevel())
			continue;

		InteractionComponent->NotifyInteractionEvent(GetOwner(), InteractionActor, EIInteractionEventType::BeginOverlap);
	}
}

//* Link Event 설정 */
void UEIInteractionComponent::SetupLinkEvent()
{

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

void UEIInteractionComponent::Server_AddUndefineData_Implementation(const TArray<FEIInteractionData>& InBeginOverlapList)
{
	m_UnDefineInteractionDataList = InBeginOverlapList;
}
//--------------------------Private_END--------------------------//

#if WITH_EDITOR
void UEIInteractionComponent::PostEditChangeProperty(struct FPropertyChangedEvent& InPropertyName)
{
	static const FName Name_ParentList = GET_MEMBER_NAME_CHECKED(UEIInteractionComponent, m_LinkParentActor);
	static const FName Name_OffsprintList = GET_MEMBER_NAME_CHECKED(UEIInteractionComponent, m_LinkOffspringActor);

	if (InPropertyName.Property != NULL)
	{
		const FName PropName = InPropertyName.MemberProperty->GetFName();

		if (PropName == Name_ParentList)
		{

		}
		else if (PropName == Name_OffsprintList)
		{
			
		}
	}

	Super::PostEditChangeProperty(InPropertyName);
}
#endif // WITH_EDITOR

