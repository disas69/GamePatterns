// Game Programming Patterns, Eugene Esaulenko, 2024

#pragma once

#include "CoreMinimal.h"
#include "FActorPoolParams.generated.h"

class APooledActor;

USTRUCT(BlueprintType)
struct FActorPoolParams
{
    GENERATED_USTRUCT_BODY()

    UPROPERTY(EditDefaultsOnly, Category = "Object Pool")
    TSubclassOf<APooledActor> ActorClass = nullptr;

    UPROPERTY(EditDefaultsOnly, Category = "Object Pool")
    int32 PoolSize = 10;

    UPROPERTY(EditDefaultsOnly, Category = "Object Pool")
    bool IsAutoExpandable = true;
};
