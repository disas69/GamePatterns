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

void UGameStateSubsystem::SetState(EGameState NewState)
{
    GameStateMachine.SetState(NewState);
}

void UGameStateSubsystem::OnOpenMenu()
{
    GameStateMachine.SetState(EGameState::InGame);
}

void UGameStateSubsystem::OnStartGame()
{
    GameStateMachine.SetState(EGameState::GameOver);
}

void UGameStateSubsystem::OnEndGame()
{
    GameStateMachine.SetState(EGameState::None);
}

void UGameStateSubsystem::InitializeStateMachine()
{
    GameStateMachine.AddTransition(EGameState::None, EGameState::MainMenu,
        [this]()
        {
            UE_LOG(LogTemp, Warning, TEXT("Opening menu"));
        });

    GameStateMachine.AddTransition(EGameState::MainMenu, EGameState::InGame,
        [this]()
        {
            UE_LOG(LogTemp, Warning, TEXT("Starting game"));
        });

    GameStateMachine.AddTransition(EGameState::InGame, EGameState::GameOver,
        [this]()
        {
            UE_LOG(LogTemp, Warning, TEXT("Ending game"));
        });
}