// Game Programming Patterns, Eugene Esaulenko, 2024

#include "ActorPoolComponent.h"
#include "ActorPool.h"
#include "PooledActor.h"

UActorPoolComponent::UActorPoolComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
}

void UActorPoolComponent::BeginPlay()
{
    Super::BeginPlay();

    if (AutoCreatePool)
    {
        CreatePool();
    }
}

void UActorPoolComponent::CreatePool()
{
    if (ActorPool != nullptr)
    {
        ActorPool->Clear();
    }
    
    ActorPool = UActorPool::CreatePool(this, ActorPoolParams);
}

int32 UActorPoolComponent::GetPoolSize() const
{
    if (ActorPool != nullptr)
    {
        return ActorPool->GetPoolSize();
    }

    return 0;
}

int32 UActorPoolComponent::GetPoolNum() const
{
    if (ActorPool != nullptr)
    {
        return ActorPool->GetPoolNum();
    }

    return 0;
}

APooledActor* UActorPoolComponent::GetActor() const
{
    if (ActorPool != nullptr)
    {
        return ActorPool->GetActor();
    }

    return nullptr;
}

void UActorPoolComponent::ReturnActor(APooledActor* Actor) const
{
    if (ActorPool != nullptr && Actor != nullptr)
    {
        if (Actor->GetOwnerPool() == ActorPool)
        {
            ActorPool->ReturnActor(Actor);
        }
        else
        {
            UE_LOG(LogTemp, Warning, TEXT("Actor does not belong to target pool: %s"), *Actor->GetName());
            Actor->Return();
        }
    }
}

void UActorPoolComponent::DestroyPool() const
{
    if (ActorPool != nullptr)
    {
        ActorPool->Clear();
    }
}
