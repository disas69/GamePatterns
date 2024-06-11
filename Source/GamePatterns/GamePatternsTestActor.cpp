// Game Programming Patterns, Eugene Esaulenko, 2024

#include "GamePatternsTestActor.h"
#include "Command/ActionCommand.h"

AGamePatternsTestActor::AGamePatternsTestActor()
{
    PrimaryActorTick.bCanEverTick = true;
}

void AGamePatternsTestActor::BeginPlay()
{
    Super::BeginPlay();

    // StartObjectPoolTest();

    // StartCommandStackTest();
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

void AGamePatternsTestActor::StartObjectPoolTest()
{
    // Initialize actor pool
    ActorPool.Initialize(GetWorld());

    // Start spawning actors
    GetWorld()->GetTimerManager().SetTimer(SpawnTimerHandle, this, &AGamePatternsTestActor::SpawnPooledActor, SpawnInterval, true);

    // Start returning actors
    GetWorld()->GetTimerManager().SetTimer(ReturnTimerHandle, this, &AGamePatternsTestActor::ReturnActorToPool, ReturnInterval, true);
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

void AGamePatternsTestActor::StartCommandStackTest()
{
    UActionCommand* MoveCommand = NewObject<UActionCommand>(this);
    MoveCommand->Initialize([this]()
    {
        UE_LOG(LogTemp, Warning, TEXT("MoveCommand::Execute"));
    },
    [this]()
    {
        UE_LOG(LogTemp, Warning, TEXT("MoveCommand::Undo"));
    });
    Commands.Add(MoveCommand);

    UActionCommand* JumpCommand = NewObject<UActionCommand>(this);
    JumpCommand->Initialize([this]()
    {
        UE_LOG(LogTemp, Warning, TEXT("JumpCommand::Execute"));
    },
    [this]()
    {
        UE_LOG(LogTemp, Warning, TEXT("JumpCommand::Undo"));
    });
    Commands.Add(JumpCommand);

    CommandStack.AddCommand(MoveCommand);
    CommandStack.AddCommand(JumpCommand);
    CommandStack.ProcessCommands();

    CommandStack.UndoLastCommand();
    
    CommandStack.AddCommand(MoveCommand);
    CommandStack.AddCommand(MoveCommand);
    CommandStack.ProcessCommands();

    while (CommandStack.GetExecutedCommandsNum() > 0)
    {
        CommandStack.UndoLastCommand();
    }
}

void AGamePatternsTestActor::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}
