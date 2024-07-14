// Game Programming Patterns, Eugene Esaulenko, 2024

#pragma once

UENUM(BlueprintType)
enum class ETestGameState : uint8
{
    None,
    MainMenu,
    InGame,
    GameOver
};