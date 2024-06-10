// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "StateMachine/EGameState.h"
#include "StateMachine/FStateMachine.h"
#include "GamePatternsGameModeBase.generated.h"

UCLASS()
class GAMEPATTERNS_API AGamePatternsGameModeBase : public AGameModeBase
{
    GENERATED_BODY()

public:
    AGamePatternsGameModeBase();

    virtual void BeginPlay() override;

private:
    TFStateMachine<EGameState> GameStateMachine;

    void InitializeStateMachine();
    void OnOpenMenu();
    void OnStartGame();
    void OnEndGame();
};
