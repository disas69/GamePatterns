// Game Programming Patterns, Eugene Esaulenko, 2024

#include "ActorPool.h"
#include "FActorPoolParams.h"
#include "PooledActor.h"

UActorPool* UActorPool::CreatePool(UObject* Outer, const FActorPoolParams Params)
{
    UActorPool* Pool = NewObject<UActorPool>(Outer);
    Pool->Initialize(Params);
    return Pool;
}

void UActorPool::Initialize(const FActorPoolParams Params)
{
    if (Params.ActorClass == nullptr)
    {
        UE_LOG(LogTemp, Error, TEXT("Object class is nullptr"));
        return;
    }

    if (!Params.ActorClass->IsChildOf<AActor>())
    {
        UE_LOG(LogTemp, Error, TEXT("Object class is not an AActor"));
        return;
    }

    PoolParams = Params;

    for (int32 i = 0; i < PoolParams.PoolSize; i++)
    {
        APooledActor* Actor = GetWorld()->SpawnActor<APooledActor>(PoolParams.ActorClass);
        Actor->Initialize(this);
        Actor->OnReturnToPool();
        Pool.Add(Actor);
    }
}

APooledActor* UActorPool::GetActor()
{
    if (PoolParams.ActorClass == nullptr)
    {
        UE_LOG(LogTemp, Error, TEXT("Object class is nullptr"));
        return nullptr;
    }
    
    if (Pool.IsEmpty())
    {
        if (PoolParams.IsAutoExpandable)
        {
            UE_LOG(LogTemp, Warning, TEXT("Pool is empty, creating new actor"));

            ++PoolParams.PoolSize;

            APooledActor* Actor = GetWorld()->SpawnActor<APooledActor>(PoolParams.ActorClass);
            if (Actor != nullptr)
            {
                Actor->Initialize(this);
                Actor->OnSpawnFromPool();
                return Actor;
            }
        }

        UE_LOG(LogTemp, Warning, TEXT("Pool is empty"));
        return nullptr;
    }

    UE_LOG(LogTemp, Warning, TEXT("Getting actor from pool"));

    const int32 Index = Pool.Num() - 1;
    APooledActor* Actor = Pool[Index];
    Pool.RemoveAt(Index);
    Actor->OnSpawnFromPool();

    return Actor;
}

void UActorPool::ReturnActor(APooledActor* Actor)
{
    if (Actor != nullptr)
    {
        Actor->OnReturnToPool();
        Pool.Add(Actor);

        UE_LOG(LogTemp, Warning, TEXT("Retured actor to pool"));
    }
}

void UActorPool::Clear()
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