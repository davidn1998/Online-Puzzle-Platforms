// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MenuInterface.h"
#include "MenuOverlay.generated.h"

/**
 * 
 */
UCLASS()
class PUZZLEPLATFORMS_API UMenuOverlay : public UUserWidget
{
	GENERATED_BODY()

private:
	bool bMenuIsShowing = false;

	UPROPERTY(meta = (BindWidget))
	class UButton *CancelButton;

	UPROPERTY(meta = (BindWidget))
	class UButton *QuitButton;

	IMenuInterface *MenuInterface;

public:
	virtual bool Initialize() override;

	void Setup();

	UFUNCTION()
	void CancelMenu();

	UFUNCTION()
	void QuitGame();

	UFUNCTION()
	void TearDown();

	UFUNCTION()
	bool GetMenuIsShowing();

	UFUNCTION()
	void SetGetMenuIsShowing(bool bIsMenuShowing);

	void SetMenuInterface(IMenuInterface *InMenuInterface);

	virtual void OnLevelRemovedFromWorld(ULevel *InLevel, UWorld *InWorld) override;
};
