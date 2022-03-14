// Fill out your copyright notice in the Description page of Project Settings.

#include "EIPlayerController.h"

AEIPlayerController::AEIPlayerController()
{

}

void AEIPlayerController::BeginPlay()
{
    Super::BeginPlay();
}

void AEIPlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();
}

void AEIPlayerController::PostInitializeComponents()
{
    Super::PostInitializeComponents();
}

void AEIPlayerController::OnPossess(APawn* InPawn)
{
    Super::OnPossess(InPawn);
}

void AEIPlayerController::ProcessPlayerInput(const float DeltaTime, const bool bGamePaused)
{
    Super::ProcessPlayerInput(DeltaTime, bGamePaused);
}

//----------------------------Public----------------------------//
//* 강제 이동 */
void AEIPlayerController::ForceMove(float DeltaTime)
{
    
}
//--------------------------Public_END--------------------------//

//----------------------------Protected----------------------------//

//--------------------------Protected_END--------------------------//


//----------------------------Private----------------------------//

//--------------------------Private_END--------------------------//