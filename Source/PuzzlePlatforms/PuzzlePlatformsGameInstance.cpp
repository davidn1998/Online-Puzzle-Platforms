// Fill out your copyright notice in the Description page of Project Settings.

#include "PuzzlePlatformsGameInstance.h"
#include "Engine.h"
#include "UObject/ConstructorHelpers.h"
#include "Blueprint/UserWidget.h"

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
    UE_LOG(LogTemp, Warning, TEXT("WBP Name: %s"), *MenuBPClass->GetName());
}

void UPuzzlePlatformsGameInstance::LoadMenu()
{
    if (!ensure(MenuBPClass != nullptr))
        return;
    UUserWidget *Menu = CreateWidget<UUserWidget>(this, MenuBPClass);
    Menu->AddToViewport();

    APlayerController *PlayerController = GetFirstLocalPlayerController();
    if (!ensure(PlayerController != nullptr))
        return;

    FInputModeUIOnly InputMode;
    InputMode.SetWidgetToFocus(Menu->TakeWidget());
    InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);

    PlayerController->SetInputMode(InputMode);
    PlayerController->bShowMouseCursor = true;
}

void UPuzzlePlatformsGameInstance::Host() const
{
    GEngine->AddOnScreenDebugMessage(0, 2.f, FColor::Green, TEXT("Hosting Game"));

    GetWorld()->ServerTravel("/Game/ThirdPersonCPP/Maps/ThirdPersonExampleMap?listen");
}

void UPuzzlePlatformsGameInstance::Join(const FString Address) const
{
    GEngine->AddOnScreenDebugMessage(1, 2.f, FColor::Green, FString::Printf(TEXT("Joining game at address: %s"), *Address));

    APlayerController *PlayerController = GetFirstLocalPlayerController();

    if (!ensure(PlayerController != nullptr))
        return;

    PlayerController->ClientTravel(Address, ETravelType::TRAVEL_Absolute);
}
