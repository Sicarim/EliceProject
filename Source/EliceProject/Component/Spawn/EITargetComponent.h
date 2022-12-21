// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "EITargetComponent.generated.h"

/**
 * 
 */

class UBillboardComponent;
class UArrowComponent;

UCLASS()
class ELICEPROJECT_API UEITargetComponent : public USceneComponent
{
	GENERATED_BODY()
	
public:
	UEITargetComponent();

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

#if WITH_EDITOR
public:
	virtual void PostEditComponentMove(bool bFinished);

	FORCEINLINE UBillboardComponent* GetSpriteComponent() const { return m_SpriteComponent; }
	FORCEINLINE UArrowComponent* GetArrowComponent() const { return m_ArrowComponent; }
#endif //WITH_EDITOR

#if WITH_EDITORONLY_DATA
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Display, meta = (AllowPrivateAccess = "true"))
	UBillboardComponent* m_SpriteComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Display, meta = (AllowPrivateAccess = "true"))
	UArrowComponent* m_ArrowComponent;
#endif
};
