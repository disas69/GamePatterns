// Game Programming Patterns, Eugene Esaulenko, 2024

#include "GameStateSubsystem.h"

UGameStateSubsystem* UGameStateSubsystem::GetInstance()
{
    const FWorldContext* WorldContextObject = GEngine->GetWorldContextFromGameViewport(GEngine->GameViewport);
    return WorldContextObject->World()->GetGameInstance()->GetSubsystem<UGameStateSubsystem>();
}

void UGameStateSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
    Super::Initialize(Collection);
    InitializeStateMachine();
}

void UGameStateSubsystem::Deinitialize()
{
    Super::Deinitialize();
}

void UGameStateSubsystem::SetState(ETestGameState NewState)
{
    GameStateMachine.SetState(NewState);
}

ETestGameState UGameStateSubsystem::GetState() const
{
    return GameStateMachine.GetCurrentState();
}

void UGameStateSubsystem::InitializeStateMachine()
{
    GameStateMachine.AddTransition(ETestGameState::None, ETestGameState::MainMenu, [this]() { UE_LOG(LogTemp, Warning, TEXT("Opening menu")); });

    GameStateMachine.AddTransition(ETestGameState::MainMenu, ETestGameState::InGame, [this]() { UE_LOG(LogTemp, Warning, TEXT("Starting game")); });

    GameStateMachine.AddTransition(ETestGameState::InGame, ETestGameState::GameOver, [this]() { UE_LOG(LogTemp, Warning, TEXT("Ending game")); });

    GameStateMachine.AddTransitions(ETestGameState::GameOver, {
        {ETestGameState::MainMenu, [this]() { UE_LOG(LogTemp, Warning, TEXT("Opening menu")); }},
        {ETestGameState::InGame, [this]() { UE_LOG(LogTemp, Warning, TEXT("Restarting game")); }}
    });
}