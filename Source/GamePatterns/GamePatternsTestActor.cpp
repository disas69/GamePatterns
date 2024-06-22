// Game Programming Patterns, Eugene Esaulenko, 2024

#include "GamePatternsTestActor.h"
#include "Command/ActionCommand.h"
#include "EventQueue/AudioEvent.h"
#include "ObjectPool/ActorPool.h"
#include "ObjectPool/PooledActor.h"
#include "ServiceLocator/AudioService.h"
#include "ServiceLocator/ServiceLocatorSubsystem.h"
#include "Singleton/GameStateSubsystem.h"

AGamePatternsTestActor::AGamePatternsTestActor()
{
    PrimaryActorTick.bCanEverTick = true;
}

void AGamePatternsTestActor::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    // Process event queue
    EventQueue.ProcessEvents();
}

void AGamePatternsTestActor::BeginPlay()
{
    Super::BeginPlay();

    // StartObjectPoolTest();

    // StartCommandStackTest();

    StartStateMachineTest();

    // StartServiceLocatorTest();

    // StartEventQueueTest();
}

void AGamePatternsTestActor::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    Super::EndPlay(EndPlayReason);

    if (ActorPool != nullptr)
    {
        while (!ActiveActors.IsEmpty())
        {
            APooledActor* Actor = ActiveActors[0];
            if (Actor != nullptr)
            {
                Actor->Return();
            }
            ActiveActors.RemoveAt(0);
        }

        ActorPool->Clear();
    }
}

void AGamePatternsTestActor::StartObjectPoolTest()
{
    // Initialize actor pool
    ActorPool = NewObject<UActorPool>(this);
    ActorPool->Initialize(ActorPoolParams);

    // Start spawning actors
    GetWorld()->GetTimerManager().SetTimer(SpawnTimerHandle, this, &AGamePatternsTestActor::SpawnPooledActor, SpawnInterval, true);

    // Start returning actors
    GetWorld()->GetTimerManager().SetTimer(ReturnTimerHandle, this, &AGamePatternsTestActor::ReturnActorToPool, ReturnInterval, true);
}

void AGamePatternsTestActor::SpawnPooledActor()
{
    if (ActorPool == nullptr)
    {
        return;
    }
    
    APooledActor* Actor = ActorPool->GetActor();
    if (Actor == nullptr)
    {
        return;
    }
    
    Actor->SetActorLocation(SpawnLocation);
    ActiveActors.Add(Actor);
}

void AGamePatternsTestActor::ReturnActorToPool()
{
    if (ActorPool == nullptr || ActiveActors.Num() == 0)
    {
        return;
    }

    ActiveActors[0]->Return();
    ActiveActors.RemoveAt(0);
}

void AGamePatternsTestActor::StartCommandStackTest()
{
    // Create and initialize action commands
    UActionCommand* MoveCommand = NewObject<UActionCommand>(this);
    MoveCommand->Initialize([this]()
    {
        UE_LOG(LogTemp, Warning, TEXT("MoveCommand::Execute"));
    }, [this]()
    {
        UE_LOG(LogTemp, Warning, TEXT("MoveCommand::Undo"));
    });
    Commands.Add(MoveCommand);

    UActionCommand* JumpCommand = NewObject<UActionCommand>(this);
    JumpCommand->Initialize([this]()
    {
        UE_LOG(LogTemp, Warning, TEXT("JumpCommand::Execute"));
    }, [this]()
    {
        UE_LOG(LogTemp, Warning, TEXT("JumpCommand::Undo"));
    });
    Commands.Add(JumpCommand);

    // Add 2 commands to the stack
    CommandStack.AddCommand(MoveCommand);
    CommandStack.AddCommand(JumpCommand);

    // Process commands
    CommandStack.ProcessCommands();

    // Undo last processed command
    CommandStack.UndoLastCommand();

    // Add 2 more commands to the stack
    CommandStack.AddCommand(MoveCommand);
    CommandStack.AddCommand(MoveCommand);

    // Process all commands
    CommandStack.ProcessCommands();

    // Undo all commands
    while (CommandStack.GetExecutedCommandsNum() > 0)
    {
        CommandStack.UndoLastCommand();
    }
}

void AGamePatternsTestActor::StartStateMachineTest()
{
    // UGameStateSubsystem is a singleton based on UGameInstanceSubsystem
    
    // Switch the state of the GameStateMachine from None to MainMenu
    UGameStateSubsystem::GetInstance()->SetState(EGameState::MainMenu);

    // To InGame
    UGameStateSubsystem::GetInstance()->SetState(EGameState::InGame);

    // To GameOver
    UGameStateSubsystem::GetInstance()->SetState(EGameState::GameOver);

    const EGameState CurrentState = UGameStateSubsystem::GetInstance()->GetState();
    UE_LOG(LogTemp, Warning, TEXT("Current state: %s"), *UEnum::GetValueAsString(CurrentState));

    // Back to InGame
    UGameStateSubsystem::GetInstance()->SetState(EGameState::InGame);
}

void AGamePatternsTestActor::StartServiceLocatorTest()
{
    // Try to resolve audio service instance that is not registered yet
    const UAudioService* AudioService = UServiceLocatorSubsystem::ResolveService<UAudioService>();
    if (AudioService != nullptr)
    {
        AudioService->PlayAudio(nullptr);
    }

    // Register new audio service instance
    UServiceLocatorSubsystem::RegisterService<UAudioService>(NewObject<UAudioService>());

    // Resolve audio service instance and play audio
    AudioService = UServiceLocatorSubsystem::ResolveService<UAudioService>();
    if (AudioService != nullptr)
    {
        AudioService->PlayAudio(nullptr);
    }

    // Unregister audio service instance
    UServiceLocatorSubsystem::UnregisterService<UAudioService>();
}

void AGamePatternsTestActor::StartEventQueueTest()
{
    GetWorld()->GetTimerManager().SetTimer(EventQueueTimerHandle, this, &AGamePatternsTestActor::EnqueueEvent, EventQueueInterval, true);
}

void AGamePatternsTestActor::EnqueueEvent()
{
    // Create and initialize audio events
    UAudioEvent* AudioEvent1 = NewObject<UAudioEvent>(this);
    AudioEvent1->Initialize(1);

    UAudioEvent* AudioEvent2 = NewObject<UAudioEvent>(this);
    AudioEvent2->Initialize(2);

    UAudioEvent* AudioEvent3 = NewObject<UAudioEvent>(this);
    AudioEvent3->Initialize(3);

    // Add events to the queue, they will be processed later in the Tick method
    EventQueue.AddEvent(AudioEvent1);
    EventQueue.AddEvent(AudioEvent2);
    EventQueue.AddEvent(AudioEvent3);
}
