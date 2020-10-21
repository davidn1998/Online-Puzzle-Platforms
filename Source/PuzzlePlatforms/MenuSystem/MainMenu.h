// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MenuInterface.h"
#include "MainMenu.generated.h"

/**
 * 
 */
UCLASS()
class PUZZLEPLATFORMS_API UMainMenu : public UUserWidget
{
	GENERATED_BODY()

private:
	// Menu Switcher
	UPROPERTY(meta = (BindWidget))
	class UWidgetSwitcher *MenuSwitcher;

	// Main Menu
	UPROPERTY(meta = (BindWidget))
	class UCanvasPanel *MainMenu;

	UPROPERTY(meta = (BindWidget))
	class UButton *HostButton;

	UPROPERTY(meta = (BindWidget))
	class UButton *JoinMenuButton;

	UPROPERTY(meta = (BindWidget))
	class UButton *QuitButton;

	// Join Menu
	UPROPERTY(meta = (BindWidget))
	class UCanvasPanel *JoinMenu;

	UPROPERTY(meta = (BindWidget))
	class UEditableTextBox *AddressInput;

	UPROPERTY(meta = (BindWidget))
	class UButton *JoinServerButton;

	UPROPERTY(meta = (BindWidget))
	class UButton *BackButton;

	IMenuInterface *MenuInterface;

public:
	virtual bool Initialize() override;

	UFUNCTION()
	void HostServer();

	UFUNCTION()
	void JoinServer();

	UFUNCTION()
	void ShowMainMenu();

	UFUNCTION()
	void ShowJoinMenu();

	UFUNCTION()
	void QuitGame();

	void SetMenuInterface(IMenuInterface *InMenuInterface);

	void Setup();
	virtual void OnLevelRemovedFromWorld(ULevel *InLevel, UWorld *InWorld) override;
};
