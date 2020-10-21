// Fill out your copyright notice in the Description page of Project Settings.

#include "MainMenu.h"
#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"
#include "Components/CanvasPanel.h"
#include "Components/EditableTextBox.h"
#include "Kismet/KismetSystemLibrary.h"

void UMainMenu::HostServer()
{
    if (!ensure(MenuInterface != nullptr))
        return;

    MenuInterface->Host();
}

void UMainMenu::JoinServer()
{
    if (!ensure(MenuInterface != nullptr))
        return;

    const FString Address = AddressInput->GetText().ToString();
    MenuInterface->Join(Address);
}

void UMainMenu::ShowMainMenu()
{
    if (!ensure(MenuSwitcher != nullptr))
        return;
    MenuSwitcher->SetActiveWidget(MainMenu);
}

void UMainMenu::ShowJoinMenu()
{
    if (!ensure(MenuSwitcher != nullptr))
        return;
    MenuSwitcher->SetActiveWidget(JoinMenu);
}

void UMainMenu::QuitGame()
{
    UE_LOG(LogTemp, Warning, TEXT("QUITING"));
    APlayerController *PlayerController = GetWorld()->GetFirstPlayerController();
    if (!ensure(PlayerController != nullptr))
        return;
    UKismetSystemLibrary::QuitGame(this, PlayerController, EQuitPreference::Quit, false);
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

    if (!ensure(JoinMenuButton != nullptr))
        return false;

    JoinMenuButton->OnClicked.AddDynamic(this, &UMainMenu::ShowJoinMenu);

    if (!ensure(JoinServerButton != nullptr))
        return false;

    JoinServerButton->OnClicked.AddDynamic(this, &UMainMenu::JoinServer);

    if (!ensure(BackButton != nullptr))
        return false;

    BackButton->OnClicked.AddDynamic(this, &UMainMenu::ShowMainMenu);

    if (!ensure(QuitButton != nullptr))
        return false;

    QuitButton->OnClicked.AddDynamic(this, &UMainMenu::QuitGame);

    Setup();

    return true;
}
