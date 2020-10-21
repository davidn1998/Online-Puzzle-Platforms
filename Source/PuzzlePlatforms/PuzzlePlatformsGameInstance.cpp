// Fill out your copyright notice in the Description page of Project Settings.

#include "PuzzlePlatformsGameInstance.h"
#include "Engine.h"
#include "UObject/ConstructorHelpers.h"
#include "Blueprint/UserWidget.h"
#include "MenuSystem/MainMenu.h"
#include "MenuSystem/MenuOverlay.h"

UPuzzlePlatformsGameInstance::UPuzzlePlatformsGameInstance()
{
    // Example of getting classes/blueprints using FClassFinder -  DO NOT DO THIS IN REAL PROJECTS - THIS IS JUST FOR LEARNING
    // ConstructorHelpers::FClassFinder<UUserWidget> MenuBPClassFinder(TEXT("/Game/MenuSystem/WBP_MainMenu"));
    // if (!ensure(MenuBPClassFinder.Class != nullptr))
    //     return;

    // MenuBPClass = MenuBPClassFinder.Class;
}

void UPuzzlePlatformsGameInstance::Init()
{
}

void UPuzzlePlatformsGameInstance::LoadMainMenu()
{
    if (!ensure(MainMenuBPClass != nullptr))
        return;
    UMainMenu *MainMenu = CreateWidget<UMainMenu>(this, MainMenuBPClass);

    MainMenu->SetMenuInterface(this);
}

void UPuzzlePlatformsGameInstance::LoadMenuOverlay()
{
    if (!ensure(MenuOverlayBPClass != nullptr))
        return;

    UMenuOverlay *MenuOverlay = CreateWidget<UMenuOverlay>(this, MenuOverlayBPClass);

    MenuOverlay->SetMenuInterface(this);
}

void UPuzzlePlatformsGameInstance::Host()
{
    GetWorld()->ServerTravel("/Game/ThirdPersonCPP/Maps/ThirdPersonExampleMap?listen");
}

void UPuzzlePlatformsGameInstance::Join(const FString &Address)
{

    APlayerController *PlayerController = GetFirstLocalPlayerController();

    if (!ensure(PlayerController != nullptr))
        return;

    PlayerController->ClientTravel(Address, ETravelType::TRAVEL_Absolute);
}

void UPuzzlePlatformsGameInstance::Quit()
{
    APlayerController *PlayerController = GetFirstLocalPlayerController();

    if (!ensure(PlayerController != nullptr))
        return;

    PlayerController->ClientTravel("/Game/ThirdPersonCPP/Maps/MainMenu", ETravelType::TRAVEL_Absolute);
}
