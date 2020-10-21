// Fill out your copyright notice in the Description page of Project Settings.

#include "MenuOverlay.h"
#include "Components/Button.h"

bool UMenuOverlay::Initialize()
{
    bool Success = Super::Initialize();
    if (!Success)
        return false;

    if (!ensure(CancelButton != nullptr))
        return false;

    CancelButton->OnClicked.AddDynamic(this, &UMenuOverlay::CancelMenu);

    if (!ensure(QuitButton != nullptr))
        return false;

    QuitButton->OnClicked.AddDynamic(this, &UMenuOverlay::QuitGame);

    Setup();

    return true;
}

void UMenuOverlay::Setup()
{
    this->AddToViewport();
    bMenuIsShowing = true;

    APlayerController *PlayerController = GetWorld()->GetFirstPlayerController();
    if (!ensure(PlayerController != nullptr))
        return;

    FInputModeUIOnly InputMode;
    InputMode.SetWidgetToFocus(this->TakeWidget());
    InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);

    PlayerController->SetInputMode(InputMode);
    PlayerController->bShowMouseCursor = true;
}

void UMenuOverlay::CancelMenu()
{
    if (bMenuIsShowing)
    {
        TearDown();
    }
}

void UMenuOverlay::QuitGame()
{
    if (!ensure(MenuInterface != nullptr))
        return;

    MenuInterface->Quit();
}

void UMenuOverlay::TearDown()
{
    this->RemoveFromViewport();
    bMenuIsShowing = false;

    FInputModeGameOnly InputMode;

    APlayerController *PlayerController = GetWorld()->GetFirstPlayerController();
    if (!ensure(PlayerController != nullptr))
        return;

    PlayerController->SetInputMode(InputMode);
    PlayerController->bShowMouseCursor = false;
}

bool UMenuOverlay::GetMenuIsShowing()
{
    return this->bMenuIsShowing;
}

void UMenuOverlay::SetGetMenuIsShowing(bool bIsMenuShowing)
{
    this->bMenuIsShowing = bMenuIsShowing;
}

void UMenuOverlay::SetMenuInterface(IMenuInterface *InMenuInterface)
{
    this->MenuInterface = InMenuInterface;
}

void UMenuOverlay::OnLevelRemovedFromWorld(ULevel *InLevel, UWorld *InWorld)
{
    Super::OnLevelRemovedFromWorld(InLevel, InWorld);
    TearDown();
}
