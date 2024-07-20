// Game Programming Patterns, Eugene Esaulenko, 2024

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PooledActor.generated.h"

class UActorPool;
struct FActorPoolParams;

UCLASS()
class GAMEPATTERNS_API APooledActor : public AActor
{
    GENERATED_BODY()

public:
    APooledActor();

    virtual void Initialize(UActorPool* Pool);
    virtual void OnSpawnFromPool();
    virtual void OnReturnToPool();

    UFUNCTION(BlueprintCallable, Category = "Object Pool")
    UActorPool* GetOwnerPool() const { return OwnerPool; }
    
    UFUNCTION(BlueprintCallable, Category = "Object Pool")
    void Return();

private:
    UPROPERTY()
    UActorPool* OwnerPool = nullptr;
};
