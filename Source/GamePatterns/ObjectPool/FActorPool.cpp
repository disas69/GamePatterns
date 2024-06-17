// Game Programming Patterns, Eugene Esaulenko, 2024

#include "FActorPool.h"
#include "PooledActor.h"

void FActorPool::Initialize(UWorld* World)
{
    if (ActorClass == nullptr)
    {
        UE_LOG(LogTemp, Error, TEXT("Object class is nullptr"));
        return;
    }

    if (!ActorClass->IsChildOf<AActor>())
    {
        UE_LOG(LogTemp, Error, TEXT("Object class is not an AActor"));
        return;
    }

    if (World == nullptr)
    {
        UE_LOG(LogTemp, Error, TEXT("World is nullptr"));
        return;
    }

    WorldContext = World;

    for (int32 i = 0; i < PoolSize; i++)
    {
        APooledActor* Actor = WorldContext->SpawnActor<APooledActor>(ActorClass);
        Actor->OnReturnToPool();
        Pool.Add(Actor);
    }
}

APooledActor* FActorPool::GetActor()
{
    if (Pool.IsEmpty())
    {
        if (IsAutoExpandable)
        {
            UE_LOG(LogTemp, Warning, TEXT("Pool is empty, creating new actor"));
            if (WorldContext != nullptr)
            {
                ++PoolSize;

                APooledActor* Actor = WorldContext->SpawnActor<APooledActor>(ActorClass);
                Actor->OnSpawnFromPool();

                return Actor;
            }
            else
            {
                UE_LOG(LogTemp, Error, TEXT("World is nullptr"));
            }
        }
        else
        {
            UE_LOG(LogTemp, Warning, TEXT("Pool is empty"));
        }

        return nullptr;
    }

    UE_LOG(LogTemp, Warning, TEXT("Getting actor from pool"));

    const int32 Index = Pool.Num() - 1;
    APooledActor* Actor = Pool[Index];
    Pool.RemoveAt(Index);
    Actor->OnSpawnFromPool();

    return Actor;
}

void FActorPool::ReturnActor(APooledActor* Actor)
{
    Actor->OnReturnToPool();
    Pool.Add(Actor);

    UE_LOG(LogTemp, Warning, TEXT("Retured actor to pool"));
}

void FActorPool::Clear()
{
    while (!Pool.IsEmpty())
    {
        const int32 Index = Pool.Num() - 1;
        APooledActor* Actor = Pool[Index];
        Pool.RemoveAt(Index);

        if (Actor != nullptr)
        {
            Actor->Destroy();
        }
    }
}
