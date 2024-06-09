// Game Programming Patterns, Eugene Esaulenko, 2024

#include "GamePatternsTestActor.h"

AGamePatternsTestActor::AGamePatternsTestActor()
{
    PrimaryActorTick.bCanEverTick = true;
}

void AGamePatternsTestActor::BeginPlay()
{
    Super::BeginPlay();

    // Initialize actor pool
    ActorPool.Initialize(GetWorld());

    // Start spawning actors
    GetWorld()->GetTimerManager().SetTimer(SpawnTimerHandle, this, &AGamePatternsTestActor::SpawnPooledActor, SpawnInterval, true);

    // Start returning actors
    GetWorld()->GetTimerManager().SetTimer(ReturnTimerHandle, this, &AGamePatternsTestActor::ReturnActorToPool, ReturnInterval, true);
}

void AGamePatternsTestActor::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    Super::EndPlay(EndPlayReason);

    while (!ActiveActors.IsEmpty())
    {
        AActor* Actor = ActiveActors[0];
        if (Actor != nullptr)
        {
            ActorPool.ReturnActor(Actor);
        }
        ActiveActors.RemoveAt(0);
    }

    ActorPool.Clear();
}

void AGamePatternsTestActor::SpawnPooledActor()
{
    AActor* Actor = ActorPool.GetActor();
    if (Actor == nullptr)
    {
        return;
    }
    
    Actor->SetActorLocation(SpawnLocation);
    ActiveActors.Add(Actor);
}

void AGamePatternsTestActor::ReturnActorToPool()
{
    if (ActiveActors.Num() == 0)
    {
        return;
    }

    ActorPool.ReturnActor(ActiveActors[0]);
    ActiveActors.RemoveAt(0);
}

void AGamePatternsTestActor::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}
