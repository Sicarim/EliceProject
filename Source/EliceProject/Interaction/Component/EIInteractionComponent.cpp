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
//* Interaction ���� */
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

	//���ͷ��� ���� �������� Ȯ��
	if (false == InteractionActor->IsEnableInteraction_Implementation(InInteractionCharacter, InEventType))
		return false;

	Character->Server_ExecuteInteractionEvent(InInteractionCharacter, InInteractionActor, InEventType);

	return true;
}

//* InteractionData ���� */
void UEIInteractionComponent::OnInsertionInteractionData(AActor* InActor, EIInteractionEventType InEventType)
{
	if (nullptr == InActor || false == InActor->IsValidLowLevel())
		return;

	FEIInteractionData* FindData = nullptr;

	//�÷��̾��� ���
	if (EIInteractionOwnerType::Interaction_Doer == m_OwnerType)
	{
		//���� �������� �ʴ� ���ͷ��� ��Ͽ��� ã�´�.
		FindData = m_UnDefineInteractionDataList.FindByPredicate([InActor](const FEIInteractionData& IsData)
			{
				return IsData.m_InteractionActor == InActor;
			});

		//���ٸ�, �̹� ������ ����Ʈ�� ������Ƿ�, ���¸� �����Ѵ�.
		if (nullptr == FindData)
		{
			FEIInteractionData* CollectData = m_InteractionDataList.FindByPredicate([InActor](const FEIInteractionData& IsData)
				{
					return IsData.m_InteractionActor == InActor;
				});

			if (nullptr != CollectData)
			{
				//State ����
				SetupInteractionState(CollectData, InEventType);
			}
		}
		//ã�Ҵٸ�...
		else
		{
			//State ����
			SetupInteractionState(FindData, InEventType);
			m_InteractionDataList.Add(*FindData);

			m_UnDefineInteractionDataList.RemoveAll([InActor](const FEIInteractionData& IsData)
				{
					return IsData.m_InteractionActor == InActor;
				});
		}
	}
	//������Ʈ�� ���
	else if (EIInteractionOwnerType::Interaction_Object == m_OwnerType)
	{
		AActor* Owner = GetOwner();

		//���� ���� �����͸� ������ �ִ��� Ȯ��
		FindData = m_InteractionDataList.FindByPredicate([InActor](const FEIInteractionData& IsData)
			{
				return IsData.m_InteractionActor == InActor;
			});

		//���ٸ�...
		if (nullptr == FindData)
		{
			//�÷��̾����׼� �� ������ �ִ��� Ȯ��
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

				//State ����
				SetupInteractionState(&PlayerData, InEventType);
				m_InteractionDataList.Add(PlayerData);
			}

			
		}
		//�ִٸ� ������ ����
		else
		{
			//State ����
			SetupInteractionState(FindData, InEventType);
		}
	}
}

//* State ���� */
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

//* InteractionData ���� */
void UEIInteractionComponent::OnRemoveInteractionData(AActor* InActor)
{
	m_InteractionDataList.RemoveAll([InActor](const FEIInteractionData& IsData)
		{
			return IsData.m_InteractionActor == InActor;
		});
}
//--------------------------Public_END--------------------------//

//----------------------------Protected----------------------------//
//* Overlap�� ���ͷ��� ã�� */
void UEIInteractionComponent::SearchInteraction()
{
	//�浹üũ�� Ŭ�󿡼���
	ENetMode OwnerNetMode = GetOwner()->GetNetMode();
	if (ENetMode::NM_DedicatedServer == OwnerNetMode)
		return;

	TArray<FHitResult> OutHits, AppendHitList;

	//Owner�� ĳ������ ���
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

		//�浹 üũ
		UKismetSystemLibrary::CapsuleTraceMultiByProfile(GetOuter(), StartTrace, EndTrace, Radius, HalfHeight, "Interaction", false, IgnoreActorList, EDrawDebugTrace::None, OutHits, true);

		AppendHitList.Append(OutHits);
	}
	//Owner�� Object�� ���
	else if (EIInteractionOwnerType::Interaction_Object == m_OwnerType)
	{
		//������Ʈ�� ��ü�� ��� �ش� ���� ����
	}

	//���ͷ��� ���� ������Ʈ
	UpdateInteractionData(AppendHitList);
}

//* ���ͷ��� ���� ������Ʈ �� ���� */
void UEIInteractionComponent::UpdateInteractionData(TArray<FHitResult>& InHitList)
{	
	TArray<FEIInteractionData> BeginOverlapList, EndOverlapList;

	//EndOverlap��
	for (FEIInteractionData& Data : m_InteractionDataList)
	{
		FHitResult* FindData = InHitList.FindByPredicate([Data](const FHitResult& IsData)
			{
				return IsData.Actor.Get() == Data.m_InteractionActor;
			});

		//�����Ͱ� ������ ��ŵ
		if (nullptr != FindData)
			continue;

		FEIInteractionData EndData;
		EndData.m_InteractionActor = Data.m_InteractionActor;

		EndOverlapList.Add(EndData);
	}

	//BeginOverlap��
	for (const FHitResult& Data : InHitList)
	{
		//�����Ͱ� ���� �ִ��� Ȯ��
		FEIInteractionData* FindData = m_InteractionDataList.FindByPredicate([Data](const FEIInteractionData& IsData)
			{
				return IsData.m_InteractionActor == Data.Actor.Get();
			});

		//�����Ͱ� �ִٸ� ��ŵ
		if (nullptr != FindData)
			continue;

		FEIInteractionData BeginData;
		BeginData.m_InteractionActor = Data.Actor.Get();
		BeginData.m_OverlapComponent = Data.GetComponent();

		BeginOverlapList.Add(BeginData);

		//�������� ���� ������ ĳ��
		m_UnDefineInteractionDataList.Append(BeginOverlapList);

		for (int32 i = 0; i < BeginOverlapList.Num(); i++)
		{
			EI_LOG(Warning, TEXT("Actor Name : %s %d"), *BeginOverlapList[i].m_InteractionActor->GetName(), BeginOverlapList.Num());
		}
	}

	//���ͷ��� ���� - EndOverlap
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
	
	//���ͷ��� ���� - BegineOverlap
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

//* Link Event ���� */
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

	//Owner�� ĳ����
	if (Cast<AEIGameCharacter>(Owner))
	{
		SetComponentTickEnabled(true);
	}
	//Owner�� ������Ʈ
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

