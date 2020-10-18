// Fill out your copyright notice in the Description page of Project Settings.

#include "MovingPlatform.h"

AMovingPlatform::AMovingPlatform()
{
    PrimaryActorTick.bCanEverTick = true;
    SetMobility(EComponentMobility::Movable);
    TargetLocation = FVector(0, 0, 0);
}

void AMovingPlatform::BeginPlay()
{
    Super::BeginPlay();

    if (HasAuthority())
    {
        SetReplicates(true);
        SetReplicateMovement(true);
    }

    GlobalStartLocation = GetActorLocation();
    GlobalTargetLocation = GetTransform().TransformPosition(TargetLocation);
}

void AMovingPlatform::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (HasAuthority())
    {
        float JourneyLength = (GlobalTargetLocation - GlobalStartLocation).Size();
        float JourneyTravelled = (GetActorLocation() - GlobalStartLocation).Size();

        if (JourneyTravelled >= JourneyLength)
        {
            FVector Temp = GlobalStartLocation;
            GlobalStartLocation = GlobalTargetLocation;
            GlobalTargetLocation = Temp;
        }

        FVector Direction = (GlobalTargetLocation - GlobalStartLocation).GetSafeNormal();

        SetActorLocation(GetActorLocation() + Direction * Speed * DeltaTime);
        // SetActorLocation(GetActorLocation() += (FVector::ForwardVector * speed * DeltaTime));
    }
}
