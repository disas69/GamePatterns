// Game Programming Patterns, Eugene Esaulenko, 2024

#pragma once

#include "CoreMinimal.h"
#include "GamePatterns/StateMachine/EGameState.h"
#include "GamePatterns/StateMachine/FStateMachine.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "GameStateSubsystem.generated.h"

UCLASS()
class GAMEPATTERNS_API UGameStateSubsystem : public UGameInstanceSubsystem
{
    GENERATED_BODY()

public:
    // Get the singleton instance of the subsystem from the game instance
    static UGameStateSubsystem* GetInstance();
    
    virtual void Initialize(FSubsystemCollectionBase& Collection) override;
    virtual void Deinitialize() override;

    void SetState(EGameState NewState);
private:
    TFStateMachine<EGameState> GameStateMachine;

    void InitializeStateMachine();
    void OnOpenMenu();
    void OnStartGame();
    void OnEndGame();
};
