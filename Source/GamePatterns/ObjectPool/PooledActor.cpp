// Game Programming Patterns, Eugene Esaulenko, 2024

#include "PooledActor.h"
#include "ActorPool.h"

APooledActor::APooledActor()
{
    PrimaryActorTick.bCanEverTick = true;
}

void APooledActor::Initialize(UActorPool* Pool)
{
    OwnerPool = Pool;
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

void APooledActor::Return()
{
    if (OwnerPool != nullptr)
    {
        OwnerPool->ReturnActor(this);
    }
}
