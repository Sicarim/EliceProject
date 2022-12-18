// Fill out your copyright notice in the Description page of Project Settings.

#include "Interaction/Actor/SpawnVolume/EISpawnVolume.h"

#include "Interaction/Actor/SpawnVolume/EISpawnInfoFactory.h"

#include "Interaction/Actor/SpawnVolume/SpawnData/EISpawnBaseData.h"
#include "Interaction/Actor/SpawnVolume/SpawnBehavior/EISpawnBaseBehavior.h"

AEISpawnVolume::AEISpawnVolume()
{

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

    UE_LOG(LogTemp, Warning, TEXT("TickTIck"));
}

//* 스폰 데이터 세팅 */
bool AEISpawnVolume::InitSpawnData()
{
    bool InitSuccess = false;

    return InitSuccess;
}

//* 스폰 시작 */
void AEISpawnVolume::StartSpawn()
{
    //스폰은 데디에서만 실행.
    ENetMode NetMode = GetNetMode();
    if (NetMode == ENetMode::NM_Client)
        return;


}

#if WITH_EDITOR
void AEISpawnVolume::PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent)
{
    const FName PropertyName_SpawnType = GET_MEMBER_NAME_CHECKED(AEISpawnVolume, m_SpawnType);
    const FName ChangePropertyName(PropertyChangedEvent.Property->GetFName());

    if (ChangePropertyName == PropertyName_SpawnType)
        CreateSpawnInfo();

    Super::PostEditChangeProperty(PropertyChangedEvent);
}

bool AEISpawnVolume::CanEditChange(const FProperty* InProperty) const
{
    const bool IsCanChange = Super::CanEditChange(InProperty);

    const FName PropertyName_SpawnBehavior = GET_MEMBER_NAME_CHECKED(AEISpawnVolume, m_SpawnData);
    const FName ChangePropertyName(InProperty->GetFName());

    if (ChangePropertyName == PropertyName_SpawnBehavior)
        return false;

    return IsCanChange;
}

//* SpawnBehavior 생성 */
void AEISpawnVolume::CreateSpawnInfo()
{
    m_SpawnData = UEISpawnInfoFactory::CreateSpawnData(m_SpawnType, this);
    m_SpawnBehavior = UEISpawnInfoFactory::CreateSpawnBehavior(m_SpawnType, this, m_SpawnData);

    if (m_SpawnData == nullptr || m_SpawnData->IsValidLowLevel() == false)
        UE_LOG(LogTemp, Error, TEXT("[AEISpawnVolume] SpawnData Create Failed"));

    if (m_SpawnBehavior == nullptr || m_SpawnBehavior->IsValidLowLevel() == false)
        UE_LOG(LogTemp, Error, TEXT("[AEISpawnVolume] SpawnBehavior Create Failed"));
}
#endif //WITH_EDITOR