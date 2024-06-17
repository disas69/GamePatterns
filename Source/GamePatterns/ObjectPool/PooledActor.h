// Game Programming Patterns, Eugene Esaulenko, 2024

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PooledActor.generated.h"

struct FActorPool;

UCLASS()
class GAMEPATTERNS_API APooledActor : public AActor
{
    GENERATED_BODY()

public:
    APooledActor();

    virtual void Tick(float DeltaTime) override;

    virtual void OnSpawnFromPool();
    virtual void OnReturnToPool();

protected:
    virtual void BeginPlay() override;
};
