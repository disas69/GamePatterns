// Copyright Epic Games, Inc. All Rights Reserved.

#include "GamePatternsGameModeBase.h"

AGamePatternsGameModeBase::AGamePatternsGameModeBase() : GameStateMachine(EGameState::None) {}

void AGamePatternsGameModeBase::BeginPlay()
{
    Super::BeginPlay();

    InitializeStateMachine();
    GameStateMachine.SetState(EGameState::MainMenu);
}

void AGamePatternsGameModeBase::InitializeStateMachine()
{
    GameStateMachine.AddTransition(EGameState::None, EGameState::MainMenu,
        [this]()
        {
            UE_LOG(LogTemp, Warning, TEXT("Opening menu"));
            OnOpenMenu();
        });

    GameStateMachine.AddTransition(EGameState::MainMenu, EGameState::InGame,
        [this]()
        {
            UE_LOG(LogTemp, Warning, TEXT("Starting game"));
            OnStartGame();
        });

    GameStateMachine.AddTransition(EGameState::InGame, EGameState::GameOver,
        [this]()
        {
            UE_LOG(LogTemp, Warning, TEXT("Ending game"));
            OnEndGame();
        });
}

void AGamePatternsGameModeBase::OnOpenMenu()
{
    GameStateMachine.SetState(EGameState::InGame);
}

void AGamePatternsGameModeBase::OnStartGame()
{
    GameStateMachine.SetState(EGameState::GameOver);
}

void AGamePatternsGameModeBase::OnEndGame()
{
    GameStateMachine.SetState(EGameState::None);
}