// Game Programming Patterns, Eugene Esaulenko, 2024

#pragma once

#include "CoreMinimal.h"
#include "FActorPool.generated.h"

USTRUCT(BlueprintType)
struct FActorPool
{
    GENERATED_USTRUCT_BODY()

    UPROPERTY(EditDefaultsOnly, Category = "Object Pool")
    TSubclassOf<AActor> ActorClass = nullptr;

    UPROPERTY(EditDefaultsOnly, Category = "Object Pool")
    int32 PoolSize = 10;

    UPROPERTY(EditDefaultsOnly, Category = "Object Pool")
    bool IsAutoExpandable = true;

    int32 GetPoolSize() const { return PoolSize; }
    int32 GetPoolNum() const { return Pool.Num(); }

    void Initialize(UWorld* World);
    AActor* GetActor();
    void ReturnActor(AActor* Actor);
    void Clear();

private:
    UPROPERTY()
    UWorld* WorldContext = nullptr;

    UPROPERTY()
    TArray<AActor*> Pool;

    void PrepareActor(AActor* Actor);
    void ResetActor(AActor* Actor);
};
