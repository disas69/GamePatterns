// Game Programming Patterns, Eugene Esaulenko, 2024

#include "FActorPool.h"

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
        AActor* Actor = WorldContext->SpawnActor<AActor>(ActorClass);
        ResetActor(Actor);
        Pool.Add(Actor);
    }
}

AActor* FActorPool::GetActor()
{
    if (Pool.IsEmpty())
    {
        if (IsAutoExpandable)
        {
            UE_LOG(LogTemp, Warning, TEXT("Pool is empty, creating new actor"));
            if (WorldContext != nullptr)
            {
                ++PoolSize;
            
                AActor* Actor = WorldContext->SpawnActor<AActor>(ActorClass);
                PrepareActor(Actor);
                
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
    AActor* Actor = Pool[Index];
    Pool.RemoveAt(Index);
    PrepareActor(Actor);
    
    return Actor;
}

void FActorPool::ReturnActor(AActor* Actor)
{
    ResetActor(Actor);
    Pool.Add(Actor);

    UE_LOG(LogTemp, Warning, TEXT("Retured actor to pool"));
}

void FActorPool::Clear()
{
    while (!Pool.IsEmpty())
    {
        const int32 Index = Pool.Num() - 1;
        AActor* Actor = Pool[Index];
        Pool.RemoveAt(Index);

        if (Actor != nullptr)
        {
            Actor->Destroy();
        }
    }
}

void FActorPool::PrepareActor(AActor* Actor)
{
    Actor->SetActorHiddenInGame(false);
    Actor->SetActorEnableCollision(true);
    
    for (UActorComponent* Component : Actor->GetComponents())
    {
        if (UPrimitiveComponent* PrimComp = Cast<UPrimitiveComponent>(Component))
        {
            PrimComp->SetSimulatePhysics(true);
        }
    }
}

void FActorPool::ResetActor(AActor* Actor)
{
    Actor->SetActorHiddenInGame(true);
    Actor->SetActorEnableCollision(false);
    
    for (UActorComponent* Component : Actor->GetComponents())
    {
        if (UPrimitiveComponent* PrimComp = Cast<UPrimitiveComponent>(Component))
        {
            PrimComp->SetSimulatePhysics(false);
        }
    }

    Actor->SetActorLocation(FVector::ZeroVector);
    Actor->SetActorRotation(FRotator::ZeroRotator);
}
