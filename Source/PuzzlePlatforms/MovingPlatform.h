// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "MovingPlatform.generated.h"

/**
 * 
 */
UCLASS()
class PUZZLEPLATFORMS_API AMovingPlatform : public AStaticMeshActor
{
	GENERATED_BODY()

private:
	FVector GlobalStartLocation;
	FVector GlobalTargetLocation;

protected:
	UPROPERTY(EditAnywhere)
	float Speed = 100.f;

	UPROPERTY(EditAnywhere, meta = (MakeEditWidget = true))
	FVector TargetLocation;

	UPROPERTY(EditAnywhere)
	int ActiveTriggers = 1;

	virtual void BeginPlay() override;

	void MovePlatform(float DeltaTime);

public:
	AMovingPlatform();
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void AddActiveTrigger();
	UFUNCTION()
	void RemoveActiveTrigger();
};
