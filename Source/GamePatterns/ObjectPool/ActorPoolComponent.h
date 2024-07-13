// Game Programming Patterns, Eugene Esaulenko, 2024

#pragma once

#include "CoreMinimal.h"
#include "FActorPoolParams.h"
#include "Components/ActorComponent.h"
#include "ActorPoolComponent.generated.h"

class UActorPool;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class GAMEPATTERNS_API UActorPoolComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UActorPoolComponent();

    UPROPERTY(EditDefaultsOnly, Category = "Object Pool")
    bool AutoCreatePool = true;

    UPROPERTY(EditDefaultsOnly, Category = "Object Pool")
    FActorPoolParams ActorPoolParams;

    UFUNCTION(BlueprintCallable, Category = "Object Pool")
    void CreatePool();

    UFUNCTION(BlueprintCallable, Category = "Object Pool")
    int32 GetPoolSize() const;

    UFUNCTION(BlueprintCallable, Category = "Object Pool")
    int32 GetPoolNum() const;

    UFUNCTION(BlueprintCallable, Category = "Object Pool")
    APooledActor* GetActor() const;

    UFUNCTION(BlueprintCallable, Category = "Object Pool")
    void ReturnActor(APooledActor* Actor) const;

    UFUNCTION(BlueprintCallable, Category = "Object Pool")
    void DestroyPool() const;

protected:
    virtual void BeginPlay() override;

private:
    UPROPERTY()
    UActorPool* ActorPool = nullptr;
};
