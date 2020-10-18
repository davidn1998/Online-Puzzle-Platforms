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

protected:
	UPROPERTY(EditAnywhere)
	float speed = 100.f;
	virtual void Tick(float DeltaTime) override;

public:
	AMovingPlatform();
	
};