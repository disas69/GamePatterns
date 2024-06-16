// Game Programming Patterns, Eugene Esaulenko, 2024

#include "GamePatternsTestActor.h"
#include "Command/ActionCommand.h"
#include "ServiceLocator/AudioService.h"
#include "ServiceLocator/ServiceLocatorSubsystem.h"
#include "Singleton/GameStateSubsystem.h"

AGamePatternsTestActor::AGamePatternsTestActor()
{
    PrimaryActorTick.bCanEverTick = false;
}

void AGamePatternsTestActor::BeginPlay()
{
    Super::BeginPlay();

    // StartObjectPoolTest();

    // StartCommandStackTest();

    // StartSingletonTest();

    StartServiceLocatorTest();
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
    MoveCommand->Initialize([this]() { UE_LOG(LogTemp, Warning, TEXT("MoveCommand::Execute")); }, [this]() { UE_LOG(LogTemp, Warning, TEXT("MoveCommand::Undo")); });
    Commands.Add(MoveCommand);

    UActionCommand* JumpCommand = NewObject<UActionCommand>(this);
    JumpCommand->Initialize([this]() { UE_LOG(LogTemp, Warning, TEXT("JumpCommand::Execute")); }, [this]() { UE_LOG(LogTemp, Warning, TEXT("JumpCommand::Undo")); });
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

void AGamePatternsTestActor::StartSingletonTest()
{
    // UGameStateSubsystem is a singleton based on UGameInstanceSubsystem
    UGameStateSubsystem::GetInstance()->SetState(EGameState::MainMenu);

    UGameStateSubsystem::GetInstance()->SetState(EGameState::InGame);

    UGameStateSubsystem::GetInstance()->SetState(EGameState::GameOver);
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
