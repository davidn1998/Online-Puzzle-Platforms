// Fill out your copyright notice in the Description page of Project Settings.

#include "PuzzlePlatformsGameInstance.h"
#include "Engine.h"

UPuzzlePlatformsGameInstance::UPuzzlePlatformsGameInstance()
{
    UE_LOG(LogTemp, Warning, TEXT("CONSTRUCTOR"));
}

void UPuzzlePlatformsGameInstance::init()
{
    UE_LOG(LogTemp, Warning, TEXT("INIT"));
}

void UPuzzlePlatformsGameInstance::Host() const
{
    GEngine->AddOnScreenDebugMessage(0, 2.f, FColor::Green, TEXT("Hosting Game"));
}

void UPuzzlePlatformsGameInstance::Join(const FString Address) const
{
    GEngine->AddOnScreenDebugMessage(1, 2.f, FColor::Green, FString::Printf(TEXT("Joining game at address: %s"), *Address));
}
