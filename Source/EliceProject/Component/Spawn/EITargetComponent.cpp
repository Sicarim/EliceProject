// Fill out your copyright notice in the Description page of Project Settings.

#include "Component/Spawn/EITargetComponent.h"

#include "Engine/Texture2D.h"
#include "UObject/ConstructorHelpers.h"

#include "Components/ArrowComponent.h"
#include "Components/BillboardComponent.h"

#include "Interaction/Actor/SpawnVolume/EISpawnVolume.h"

UEITargetComponent::UEITargetComponent()
{
#if WITH_EDITORONLY_DATA
	m_SpriteComponent = CreateEditorOnlyDefaultSubobject<UBillboardComponent>(TEXT("TargetSprite"));
	m_ArrowComponent = CreateEditorOnlyDefaultSubobject<UArrowComponent>(TEXT("TargetArrow"));

	if (!IsRunningCommandlet())
	{
		// Structure to hold one-time initialization
		struct FConstructorStatics
		{
			ConstructorHelpers::FObjectFinderOptional<UTexture2D> TargetIconSpawnObject;
			ConstructorHelpers::FObjectFinderOptional<UTexture2D> TargetIconObject;
			FName ID_TargetPoint;
			FText NAME_TargetPoint;
			FConstructorStatics()
				: TargetIconSpawnObject(TEXT("/Engine/EditorMaterials/TargetIconSpawn"))
				, TargetIconObject(TEXT("/Engine/EditorMaterials/TargetIcon"))
				, ID_TargetPoint(TEXT("TargetPoint"))
				, NAME_TargetPoint(NSLOCTEXT("SpriteCategory", "TargetPoint", "Target Points"))
			{
			}
		};
		static FConstructorStatics ConstructorStatics;

		if (m_SpriteComponent)
		{
			m_SpriteComponent->Sprite = ConstructorStatics.TargetIconObject.Get();
			m_SpriteComponent->SetRelativeScale3D_Direct(FVector(0.35f, 0.35f, 0.35f));
			m_SpriteComponent->SpriteInfo.Category = ConstructorStatics.ID_TargetPoint;
			m_SpriteComponent->SpriteInfo.DisplayName = ConstructorStatics.NAME_TargetPoint;
			m_SpriteComponent->bIsScreenSizeScaled = true;

			m_SpriteComponent->SetupAttachment(this);
		}

		if (m_ArrowComponent)
		{
			m_ArrowComponent->ArrowColor = FColor(150, 200, 255);

			m_ArrowComponent->ArrowSize = 0.5f;
			m_ArrowComponent->bTreatAsASprite = true;
			m_ArrowComponent->SpriteInfo.Category = ConstructorStatics.ID_TargetPoint;
			m_ArrowComponent->SpriteInfo.DisplayName = ConstructorStatics.NAME_TargetPoint;
			m_ArrowComponent->SetupAttachment(m_SpriteComponent);
			m_ArrowComponent->bIsScreenSizeScaled = true;

			// Counteract the scaled down parent so that the arrow is large enough to see.
			if (m_SpriteComponent)
			{
				m_ArrowComponent->SetRelativeScale3D((FVector::OneVector / m_SpriteComponent->GetRelativeScale3D()));
			}
		}
	}
#endif // WITH_EDITORONLY_DATA
}

void UEITargetComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	m_SpriteComponent->DestroyComponent();
	m_ArrowComponent->DestroyComponent();
}

#if WITH_EDITOR
void UEITargetComponent::PostEditComponentMove(bool bFinished)
{
	Super::PostEditComponentMove(bFinished);

	AEISpawnVolume* SpawnVolume = Cast<AEISpawnVolume>(GetOwner());
	if (SpawnVolume != nullptr && SpawnVolume->IsValidLowLevel() == true)
		SpawnVolume->UpdateTargetPointPosition(this);
}
#endif //WITH_EDITOR