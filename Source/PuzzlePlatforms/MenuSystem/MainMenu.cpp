// Fill out your copyright notice in the Description page of Project Settings.

#include "MainMenu.h"
#include "UMG/Public/Components/Button.h"

void UMainMenu::HostServer()
{
    if (!ensure(MenuInterface != nullptr))
        return;

    MenuInterface->Host();
}

void UMainMenu::JoinServer()
{
    UE_LOG(LogTemp, Warning, TEXT("JOINING SERVER"));
}

void UMainMenu::SetMenuInterface(IMenuInterface *InMenuInterface)
{
    this->MenuInterface = InMenuInterface;
}

void UMainMenu::Setup()
{
    this->AddToViewport();

    APlayerController *PlayerController = GetWorld()->GetFirstPlayerController();
    if (!ensure(PlayerController != nullptr))
        return;

    FInputModeUIOnly InputMode;
    InputMode.SetWidgetToFocus(this->TakeWidget());
    InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);

    PlayerController->SetInputMode(InputMode);
    PlayerController->bShowMouseCursor = true;
}

void UMainMenu::OnLevelRemovedFromWorld(ULevel *InLevel, UWorld *InWorld)
{
    Super::OnLevelRemovedFromWorld(InLevel, InWorld);
    FInputModeGameOnly InputMode;

    APlayerController *PlayerController = GetWorld()->GetFirstPlayerController();
    if (!ensure(PlayerController != nullptr))
        return;

    PlayerController->SetInputMode(InputMode);
    PlayerController->bShowMouseCursor = false;
}

bool UMainMenu::Initialize()
{
    bool Success = Super::Initialize();
    if (!Success)
        return false;
    if (!ensure(HostButton != nullptr))
        return false;

    HostButton->OnClicked.AddDynamic(this, &UMainMenu::HostServer);

    if (!ensure(JoinButton != nullptr))
        return false;

    JoinButton->OnClicked.AddDynamic(this, &UMainMenu::JoinServer);

    Setup();

    return true;
}
