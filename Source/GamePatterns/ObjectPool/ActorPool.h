// Game Programming Patterns, Eugene Esaulenko, 2024

#pragma once

#include "CoreMinimal.h"
#include "FActorPoolParams.h"
#include "UObject/Object.h"
#include "ActorPool.generated.h"

class APooledActor;

UCLASS()
class GAMEPATTERNS_API UActorPool : public UObject
{
    GENERATED_BODY()

public:
    UActorPool() = default;

    void Initialize(const FActorPoolParams& Params);

    int32 GetPoolSize() const { return PoolParams.PoolSize; }
    int32 GetPoolNum() const { return Pool.Num(); }

    APooledActor* GetActor();
    void ReturnActor(APooledActor* Actor);
    void Clear();

private:
    FActorPoolParams PoolParams;
    
    UPROPERTY()
    TArray<APooledActor*> Pool;
};
