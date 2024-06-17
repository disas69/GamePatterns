// Game Programming Patterns, Eugene Esaulenko, 2024

#include "PooledActor.h"

APooledActor::APooledActor()
{
    PrimaryActorTick.bCanEverTick = true;
}

void APooledActor::BeginPlay()
{
    Super::BeginPlay();
}

void APooledActor::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void APooledActor::OnSpawnFromPool()
{
    SetActorHiddenInGame(false);
    SetActorEnableCollision(true);

    for (UActorComponent* Component : GetComponents())
    {
        if (UPrimitiveComponent* PrimComp = Cast<UPrimitiveComponent>(Component))
        {
            PrimComp->SetSimulatePhysics(true);
        }
    }
}

void APooledActor::OnReturnToPool()
{
    SetActorHiddenInGame(true);
    SetActorEnableCollision(false);

    for (UActorComponent* Component : GetComponents())
    {
        if (UPrimitiveComponent* PrimComp = Cast<UPrimitiveComponent>(Component))
        {
            PrimComp->SetSimulatePhysics(false);
        }
    }

    SetActorLocation(FVector::ZeroVector);
    SetActorRotation(FRotator::ZeroRotator);
}
