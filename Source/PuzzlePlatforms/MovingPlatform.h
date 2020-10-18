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

	UPROPERTY(EditAnywhere, meta=(MakeEditWidget = true))
	FVector TargetLocation;

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

public:
	AMovingPlatform();
	
};
