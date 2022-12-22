// Fill out your copyright notice in the Description page of Project Settings.

#include "Interaction/Actor/SpawnVolume/EISpawnVolume.h"

#include "Interaction/Actor/SpawnVolume/EISpawnInfoFactory.h"

#include "Components/SphereComponent.h"
#include "Components/SceneComponent.h"

#include "Component/Spawn/EITargetComponent.h"

#include "Interaction/Actor/SpawnVolume/SpawnData/EISpawnBaseData.h"
#include "Interaction/Actor/SpawnVolume/SpawnBehavior/EISpawnBaseBehavior.h"

#include "Editor.h"
#include "Engine/Engine.h"
#include "Engine/Selection.h"
#include "Editor/EditorEngine.h"
#include "NavigationSystem.h"

AEISpawnVolume::AEISpawnVolume()
{
    m_SphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("VolumeSphereCollision"));
    if (m_SphereCollision != nullptr)
        m_SphereCollision->SetupAttachment(RootComponent);

    InteractionComponent->SetInteractionObjectType(EIInteractionObjectType::MonsterSpawnVolume);
}

void AEISpawnVolume::BeginPlay()
{
    Super::BeginPlay();

    bool IsSuccess = InitSpawnData();
    if (IsSuccess == false)
    {
        UE_LOG(LogTemp, Warning, TEXT("[AEISpawnVolume] InitSpawnData is Failed"));
        return;
    }

    if (m_SpawnExecuteType == EISpawnExecuteType::Start)
        StartSpawn();
}

void AEISpawnVolume::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

}

//* ���� ������ ���� */
bool AEISpawnVolume::InitSpawnData()
{
    if (m_SpawnBehavior == nullptr || m_SpawnBehavior->IsValidLowLevel() == false)
    {
        UE_LOG(LogTemp, Warning, TEXT("[AEISpawnVolume] SpawnBehavior is nullptr"));
        return false;
    }
    if (m_SpawnData == nullptr || m_SpawnData->IsValidLowLevel() == false)
    {
        UE_LOG(LogTemp, Warning, TEXT("[AEISpawnVolume] m_SpawnData is nullptr"));
        return false;
    }

    for (int32 i = 0; i < m_SpawnData->m_SpawnDataInfoList.Num(); i++)
    {
        m_SpawnData->m_SpawnDataInfoList[i].m_Yaw = m_SpawnData->m_SpawnDataInfoList[i].m_TargetPoint->GetRelativeRotation().Yaw;
        m_SpawnData->m_SpawnDataInfoList[i].m_SpawnPosition = m_SpawnData->m_SpawnDataInfoList[i].m_TargetPoint->GetComponentLocation();
    }

    m_SpawnBehavior->InitSpawnData(this, m_SpawnData);

    return true;
}

//* ���� ���� */
void AEISpawnVolume::StartSpawn()
{
    //������ ���𿡼��� ����.
    ENetMode NetMode = GetNetMode();
    if (NetMode == ENetMode::NM_Client)
        return;

    if (m_SpawnBehavior == nullptr || m_SpawnBehavior->IsValidLowLevel() == false)
    {
        UE_LOG(LogTemp, Warning, TEXT("[AEISpawnVolume] SpawnBehavior is nullptr"));
        return;
    }

    //���� ����.
    bool IsSuccess = m_SpawnBehavior->OnStartSpawn();
    if (IsSuccess == false)
    {
        UE_LOG(LogTemp, Warning, TEXT("[AEISpawnVolume] Spawn Failed!!!"));
        return;
    }
}

#if WITH_EDITOR
void AEISpawnVolume::PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent)
{
    const FName PropertyName_SpawnType = GET_MEMBER_NAME_CHECKED(AEISpawnVolume, m_SpawnType);
    const FName PropertyName_SpawnData = GET_MEMBER_NAME_CHECKED(AEISpawnVolume, m_SpawnData);

    const FName ChangePropertyName(PropertyChangedEvent.Property->GetFName());

    if (ChangePropertyName == PropertyName_SpawnType)
        CreateSpawnInfo();
    else if (ChangePropertyName == PropertyName_SpawnData)
        UpdateSpawnDataInfo();

    Super::PostEditChangeProperty(PropertyChangedEvent);
}

bool AEISpawnVolume::CanEditChange(const FProperty* InProperty) const
{
    const bool IsCanChange = Super::CanEditChange(InProperty);

    const FName PropertyName_SpawnData = GET_MEMBER_NAME_CHECKED(AEISpawnVolume, m_SpawnData);
    const FName ChangePropertyName(InProperty->GetFName());

    if (ChangePropertyName == PropertyName_SpawnData)
        return false;

    return IsCanChange;
}

//* SpawnBehavior ���� */
void AEISpawnVolume::CreateSpawnInfo()
{
    m_SpawnData = UEISpawnInfoFactory::CreateSpawnData(m_SpawnType, this);
    m_SpawnBehavior = UEISpawnInfoFactory::CreateSpawnBehavior(m_SpawnType, this, m_SpawnData);

    if (m_SpawnData == nullptr || m_SpawnData->IsValidLowLevel() == false)
        UE_LOG(LogTemp, Error, TEXT("[AEISpawnVolume] SpawnData Create Failed"));

    if (m_SpawnBehavior == nullptr || m_SpawnBehavior->IsValidLowLevel() == false)
        UE_LOG(LogTemp, Error, TEXT("[AEISpawnVolume] SpawnBehavior Create Failed"));
}

//* SpawnData ����. */
void AEISpawnVolume::UpdateSpawnDataInfo()
{
    //TargetPoint ����.
    ReleaseTargetPoint();

    //TargetPoint ����.
    CreateTargetPoint();

    USelection* SelectedActors = GEditor->GetSelectedActors();
    if (SelectedActors != nullptr)
        GEditor->SelectActor(this, true, true, true, true);
}

//TargetPoint ����.
void AEISpawnVolume::CreateTargetPoint()
{
    if (m_SpawnData == nullptr || m_SpawnData->IsValidLowLevel() == false)
    {
        UE_LOG(LogTemp, Error, TEXT("[AEISpawnVolume] SpawnData is nullptr"));
        return;
    }

    for (int32 i = 0; i < m_SpawnData->m_SpawnDataInfoList.Num(); i++)
    {
        FString ComponentName = FString::Printf(TEXT("TargetComponent_%d"), i);
        UEITargetComponent* TargetPoint = NewObject<UEITargetComponent>(this, *ComponentName);
        if (TargetPoint != nullptr)
        {
            USceneComponent* TargetScene = Cast<USceneComponent>(TargetPoint);
            if (TargetScene != nullptr)
            {
                TargetScene->OnComponentCreated();
                AddInstanceComponent(TargetScene);
                TargetScene->RegisterComponent();
                TargetScene->AttachToComponent(RootComponent, FAttachmentTransformRules::SnapToTargetNotIncludingScale);

                m_SpawnData->m_SpawnDataInfoList[i].m_TargetPoint = TargetPoint;

                // >> ��ġ ����
                FVector SpawnPosition = FVector::ZeroVector;
                if (m_SpawnData->m_SpawnDataInfoList[i].m_SpawnPosition == FVector::ZeroVector)
                    SpawnPosition = GetActorLocation();
                else
                    SpawnPosition = m_SpawnData->m_SpawnDataInfoList[i].m_SpawnPosition;

                m_SpawnData->m_SpawnDataInfoList[i].m_TargetPoint->SetWorldLocation(SpawnPosition);
                m_SpawnData->m_SpawnDataInfoList[i].m_SpawnPosition = SpawnPosition;
                // << 

                // >> ���� ����
                float Yaw = 0.f;
                if (m_SpawnData->m_SpawnDataInfoList[i].m_Yaw == 0.f)
                    Yaw = 0.f;
                else
                    Yaw = m_SpawnData->m_SpawnDataInfoList[i].m_Yaw;

                FRotator TargetRotator = m_SpawnData->m_SpawnDataInfoList[i].m_TargetPoint->GetComponentRotation();
                m_SpawnData->m_SpawnDataInfoList[i].m_TargetPoint->SetWorldRotation(FRotator(TargetRotator.Pitch, Yaw, TargetRotator.Roll));
                m_SpawnData->m_SpawnDataInfoList[i].m_Yaw = Yaw;
                // <<
            }
        }
    }
}

//TargetPoint ����.
void AEISpawnVolume::ReleaseTargetPoint()
{
    TArray<UEITargetComponent*> TargetComponentList;
    GetComponents(TargetComponentList);

    for (UEITargetComponent* Target : TargetComponentList)
    {
        if (Target == nullptr || Target->IsValidLowLevel() == false)
            continue;

        Target->DetachFromComponent(FDetachmentTransformRules::KeepRelativeTransform);
        Target->DestroyComponent();
        Target = nullptr;
    }

    for (int32 i = 0; i < m_SpawnData->m_SpawnDataInfoList.Num(); i++)
    {
        m_SpawnData->m_SpawnDataInfoList[i].m_TargetPoint = nullptr;
    }
}

//* Target ��ġ ������Ʈ */
void AEISpawnVolume::UpdateTargetPointPosition(UEITargetComponent* InTargetComponent)
{
    if (InTargetComponent == nullptr || InTargetComponent->IsValidLowLevel() == false)
    {
        UE_LOG(LogTemp, Error, TEXT("[AEISpawnVolume] InTargetComponent is nullptr"));
        return;
    }

    if (m_SpawnData == nullptr || m_SpawnData->IsValidLowLevel() == false)
        UE_LOG(LogTemp, Error, TEXT("[AEISpawnVolume] SpawnData is nullptr"));

    for (int32 i = 0; i < m_SpawnData->m_SpawnDataInfoList.Num(); i++)
    {
        if (m_SpawnData->m_SpawnDataInfoList[i].m_TargetPoint == InTargetComponent)
        {
            m_SpawnData->m_SpawnDataInfoList[i].m_Yaw = InTargetComponent->GetComponentRotation().Yaw;
            m_SpawnData->m_SpawnDataInfoList[i].m_SpawnPosition = InTargetComponent->GetComponentLocation();

            //TargetPoint��ġ�� Nav�������� ���� ��Ų��.
            UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetNavigationSystem(GetWorld());
            if (NavSystem != nullptr && NavSystem->IsValidLowLevel() == true)
            {
                FNavLocation NavLocation;
                bool IsSuccess = NavSystem->ProjectPointToNavigation(m_SpawnData->m_SpawnDataInfoList[i].m_SpawnPosition, NavLocation);
                if (IsSuccess == true)
                {
                    m_SpawnData->m_SpawnDataInfoList[i].m_SpawnPosition = NavLocation.Location + FVector(0.f, 0.f, 10.f);
                    m_SpawnData->m_SpawnDataInfoList[i].m_TargetPoint->SetWorldLocation(m_SpawnData->m_SpawnDataInfoList[i].m_SpawnPosition);
                }
            }
            break;
        }
    }
}
#endif //WITH_EDITOR