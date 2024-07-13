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

    // Actor pool factory method, the only way to create an actor pool
    static UActorPool* CreatePool(UObject* Outer, const FActorPoolParams Params);
    
    int32 GetPoolSize() const { return PoolParams.PoolSize; }
    int32 GetPoolNum() const { return Pool.Num(); }

    APooledActor* GetActor();
    void ReturnActor(APooledActor* Actor);
    void Clear();

private:
    FActorPoolParams PoolParams;
    
    UPROPERTY()
    TArray<APooledActor*> Pool;

    void Initialize(const FActorPoolParams Params);
};
