// Game Programming Patterns, Eugene Esaulenko, 2024

#include "TestActor.h"
#include "../Command/ActionCommand.h"
#include "../EventQueue/AudioEvent.h"
#include "../ObjectPool/ActorPoolComponent.h"
#include "../ObjectPool/PooledActor.h"
#include "../ServiceLocator/AudioService.h"
#include "../ServiceLocator/ServiceLocatorSubsystem.h"
#include "../Singleton/GameStateSubsystem.h"

ATestActor::ATestActor()
{
    PrimaryActorTick.bCanEverTick = true;
    ActorPoolComponent = CreateDefaultSubobject<UActorPoolComponent>(TEXT("ActorPoolComponent"));
}

void ATestActor::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    // Process event queue
    EventQueue.ProcessEvents();
}

void ATestActor::BeginPlay()
{
    Super::BeginPlay();

    // StartObjectPoolTest();

    // StartCommandStackTest();

    // StartStateMachineTest();

    // StartServiceLocatorTest();

    // StartEventQueueTest();
}

void ATestActor::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    Super::EndPlay(EndPlayReason);

    while (!ActiveActors.IsEmpty())
    {
        APooledActor* Actor = ActiveActors[0];
        if (Actor != nullptr)
        {
            Actor->Return();
        }
        ActiveActors.RemoveAt(0);
    }

    ActorPoolComponent->DestroyPool();
}

void ATestActor::StartObjectPoolTest()
{
    // Initialize actor pool
    ActorPoolComponent->CreatePool();

    // Start spawning actors
    GetWorld()->GetTimerManager().SetTimer(SpawnTimerHandle, this, &ATestActor::SpawnPooledActor, SpawnInterval, true);

    // Start returning actors
    GetWorld()->GetTimerManager().SetTimer(ReturnTimerHandle, this, &ATestActor::ReturnActorToPool, ReturnInterval, true);
}

void ATestActor::SpawnPooledActor()
{
    APooledActor* Actor = ActorPoolComponent->GetActor();
    if (Actor == nullptr)
    {
        return;
    }
    
    Actor->SetActorLocation(SpawnLocation);
    ActiveActors.Add(Actor);
}

void ATestActor::ReturnActorToPool()
{
    if (ActiveActors.Num() == 0)
    {
        return;
    }

    ActiveActors[0]->Return();
    ActiveActors.RemoveAt(0);
}

void ATestActor::StartCommandStackTest()
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

void ATestActor::StartStateMachineTest()
{
    // UGameStateSubsystem is a singleton based on UGameInstanceSubsystem
    
    // Switch the state of the GameStateMachine from None to MainMenu
    UGameStateSubsystem::GetInstance()->SetState(ETestGameState::MainMenu);

    // To InGame
    UGameStateSubsystem::GetInstance()->SetState(ETestGameState::InGame);

    // To GameOver
    UGameStateSubsystem::GetInstance()->SetState(ETestGameState::GameOver);

    const ETestGameState CurrentState = UGameStateSubsystem::GetInstance()->GetState();
    UE_LOG(LogTemp, Warning, TEXT("Current state: %s"), *UEnum::GetValueAsString(CurrentState));

    // Back to InGame
    UGameStateSubsystem::GetInstance()->SetState(ETestGameState::InGame);
}

void ATestActor::StartServiceLocatorTest()
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

void ATestActor::StartEventQueueTest()
{
    GetWorld()->GetTimerManager().SetTimer(EventQueueTimerHandle, this, &ATestActor::EnqueueEvent, EventQueueInterval, true);
}

void ATestActor::EnqueueEvent()
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
