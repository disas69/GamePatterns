// Game Programming Patterns, Eugene Esaulenko, 2024

#pragma once

#include "CoreMinimal.h"
#include "Command/FCommandStack.h"
#include "EventQueue/FEventQueue.h"
#include "GameFramework/Actor.h"
#include "ObjectPool/FActorPool.h"
#include "GamePatternsTestActor.generated.h"

class UActionCommand;

UCLASS()
class GAMEPATTERNS_API AGamePatternsTestActor : public AActor
{
    GENERATED_BODY()

public:
    AGamePatternsTestActor();

    UPROPERTY(EditDefaultsOnly, Category = "Object Pool")
    FActorPool ActorPool;

    UPROPERTY(EditDefaultsOnly, Category = "Object Pool")
    FVector SpawnLocation = FVector::ZeroVector;

    UPROPERTY(EditDefaultsOnly, Category = "Object Pool")
    float SpawnInterval = 1.0f;

    UPROPERTY(EditDefaultsOnly, Category = "Object Pool")
    float ReturnInterval = 1.0f;

    UPROPERTY(EditDefaultsOnly, Category = "Command Stack")
    FCommandStack CommandStack;

    UPROPERTY(EditDefaultsOnly, Category = "Event Queue")
    FEventQueue EventQueue;

    UPROPERTY(EditDefaultsOnly, Category = "Event Queue")
    float EventQueueInterval = 1.0f;

    virtual void Tick(float DeltaTime) override;

protected:
    virtual void BeginPlay() override;
    virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

private:
    FTimerHandle SpawnTimerHandle;
    FTimerHandle ReturnTimerHandle;
    FTimerHandle EventQueueTimerHandle;

    UPROPERTY()
    TArray<AActor*> ActiveActors;

    UPROPERTY()
    TArray<UActionCommand*> Commands;

    void StartObjectPoolTest();
    void SpawnPooledActor();
    void ReturnActorToPool();
    void StartCommandStackTest();
    void StartStateMachineTest();
    void StartServiceLocatorTest();
    void StartEventQueueTest();
    void EnqueueEvent();
};
