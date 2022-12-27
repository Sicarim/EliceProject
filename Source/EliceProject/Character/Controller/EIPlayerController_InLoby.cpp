// Fill out your copyright notice in the Description page of Project Settings.

#include "Character/Controller/EIPlayerController_InLoby.h"

#include "EliceProject.h"

#include "GameInstance/EIGameUISystem.h"
#include "Library_System/EIFunctionLibrary_System.h"

#include "UI/Main/Form/EIMain_Loby_Form.h"

#include "GameInstance/EIUIDefine.h"

AEIPlayerController_InLoby::AEIPlayerController_InLoby()
{

}

void AEIPlayerController_InLoby::BeginPlay()
{
    Super::BeginPlay();

    InitUIData();
}

void AEIPlayerController_InLoby::SetupInputComponent()
{
    Super::SetupInputComponent();
}

void AEIPlayerController_InLoby::PostInitializeComponents()
{
    Super::PostInitializeComponents();
}

void AEIPlayerController_InLoby::OnPossess(APawn* InPawn)
{
    Super::OnPossess(InPawn);
}

void AEIPlayerController_InLoby::ProcessPlayerInput(const float DeltaTime, const bool bGamePaused)
{
    Super::ProcessPlayerInput(DeltaTime, bGamePaused);
}

void AEIPlayerController_InLoby::InitUIData()
{
    UEIGameUISystem* UISystem = UEIFunctionLibrary_System::GetUISystem(this);
    if (UISystem == nullptr || UISystem->IsValidLowLevel() == false)
    {
        EI_LOG(Warning, TEXT("[AEIPlayerController_InLoby] UISystem is nullptr"));
        return;
    }

    UUserWidget* UserWidget = UISystem->Show(this, EIWidgetType::MainLoby);
    if (UISystem == nullptr || UISystem->IsValidLowLevel() == false)
    {
        EI_LOG(Warning, TEXT("[AEIPlayerController_InLoby] UISystem is nullptr"));
        return;
    }

    m_MainLobyWidget = Cast<UEIMain_Loby_Form>(UserWidget);
    if (m_MainLobyWidget == nullptr || m_MainLobyWidget->IsValidLowLevel() == false)
    {
        EI_LOG(Warning, TEXT("[AEIPlayerController_InLoby] m_MainLobyWidget is nullptr"));
        return;
    }

    bShowMouseCursor = true;
}