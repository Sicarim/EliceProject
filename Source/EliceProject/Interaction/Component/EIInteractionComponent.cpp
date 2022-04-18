// Fill out your copyright notice in the Description page of Project Settings.

#include "Interaction/Component/EIInteractionComponent.h"

#include "Net/UnrealNetwork.h"

#include "Library_System/EIFunctionLibrary_System.h"
#include "Interaction/Interface/EIInteractionSystem.h"

#include "Character/Common/EIGameCharacter.h"

UEIInteractionComponent::UEIInteractionComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

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

//--------------------------Public_END--------------------------//


//----------------------------Protected----------------------------//
//* Overlap한 인터랙션 찾기 */
void UEIInteractionComponent::SearchInteraction()
{

	//Owner가 캐릭터인 경우


	//Owner가 Object인 경우


	UpdateInteractionData();
}

//* 인터랙션 정보 업데이트 */
void UEIInteractionComponent::UpdateInteractionData()
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
	if (Cast<AEIGameCharacter>(GetOwner()))
	{
		Owner->SetActorTickEnabled(true);
	}
	//Owner가 오브젝트
	else if (Cast<AEIGameCharacter>(GetOwner()))
	{
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






