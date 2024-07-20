// Game Programming Patterns, Eugene Esaulenko, 2024

#pragma once

#include "CoreMinimal.h"
#include "../StateMachine/TestGameState.h"
#include "../StateMachine/StateMachine.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "GameStateSubsystem.generated.h"

UCLASS()
class GAMEPATTERNS_API UGameStateSubsystem : public UGameInstanceSubsystem
{
    GENERATED_BODY()

public:
    // Get the singleton instance of the subsystem from the game instance
    UFUNCTION(BlueprintCallable, Category = "Game State")
    static UGameStateSubsystem* GetInstance();

    virtual void Initialize(FSubsystemCollectionBase& Collection) override;
    virtual void Deinitialize() override;

    UFUNCTION(BlueprintCallable, Category = "Game State")
    void SetState(ETestGameState NewState);

    UFUNCTION(BlueprintCallable, Category = "Game State")
    ETestGameState GetState() const;

private:
    TStateMachine<ETestGameState> GameStateMachine;

    void InitializeStateMachine();
};
